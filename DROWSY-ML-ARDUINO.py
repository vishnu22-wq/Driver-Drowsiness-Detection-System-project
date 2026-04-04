import cv2
import mediapipe as mp
import time
import serial

arduino = serial.Serial('COM7', 9600, timeout=1)
time.sleep(2)

mp_face_mesh = mp.solutions.face_mesh
face_mesh = mp_face_mesh.FaceMesh(refine_landmarks=True)

LEFT_EYE = [33, 160, 158, 133, 153, 144]
RIGHT_EYE = [362, 385, 387, 263, 373, 380]

def EAR(eye_points, landmarks):
    p1 = landmarks[eye_points[0]]
    p2 = landmarks[eye_points[1]]
    p3 = landmarks[eye_points[2]]
    p4 = landmarks[eye_points[3]]
    p5 = landmarks[eye_points[4]]
    p6 = landmarks[eye_points[5]]

    vertical = (abs(p2.y - p6.y) + abs(p3.y - p5.y)) / 2
    horizontal = abs(p1.x - p4.x)

    return vertical / horizontal

cap = cv2.VideoCapture(0)

CLOSED_EYES_SECONDS = 1.0
start_drowsy_time = None
drowsy_state = False

while True:
    ret, frame = cap.read()
    if not ret:
        break

    rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = face_mesh.process(rgb)

    send_value = b'0'  # default NORMAL

    if results.multi_face_landmarks:
        mesh = results.multi_face_landmarks[0].landmark

        leftEAR = EAR(LEFT_EYE, mesh)
        rightEAR = EAR(RIGHT_EYE, mesh)
        avgEAR = (leftEAR + rightEAR) / 2

        # Eyes closed
        if avgEAR < 0.20:
            if start_drowsy_time is None:
                start_drowsy_time = time.time()

            if time.time() - start_drowsy_time >= CLOSED_EYES_SECONDS:
                send_value = b'1'   # DROWSY
                cv2.putText(frame, "DROWSINESS DETECTED!", (50, 80),
                            cv2.FONT_HERSHEY_SIMPLEX, 1.2, (0, 0, 255), 3)

        else:
            start_drowsy_time = None
            send_value = b'0'  # NORMAL

    # -----------------------------
    # ALWAYS PRINT THE VALUE
    # -----------------------------
#    print(send_value.decode())

    # Send to Arduino
    arduino.write(send_value)

    cv2.imshow("Drowsiness Detection", frame)

    if cv2.waitKey(1) & 0xFF == 27:
        break

cap.release()
arduino.close()
cv2.destroyAllWindows()
