import cv2
from cvzone.HandTrackingModule import HandDetector
import socket


# Define the IP address and port to connect to
ip = ''
port = 8080

# Create a socket object
conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the specified IP address and port
conn.connect((ip, port))

#CV algorithm to detect hand signs

vid=cv2.VideoCapture(0)
k='a'
det=HandDetector(detectionCon=0.5,maxHands=2)
data=k
while True:
    _ , frame=vid.read()
    hands,frame=det.findHands(frame)
    
        
    if hands:
        hand1=hands[0]
        fingers=det.fingersUp(hand1)
        font = cv2.FONT_HERSHEY_SIMPLEX
        font_scale = 1
        font_thickness = 2
        text_color = (255, 0 ,0)
        text_position = (50, 150)

        for i, finger in enumerate(fingers):
            cv2.putText(frame, str(finger), (text_position[0] + i * 80, text_position[1]), font, font_scale, text_color, font_thickness)
        if fingers[1] ==1 and fingers[2]==0 and fingers[3]==0 and fingers[4]==0:
            cv2.putText(frame,"Forward", (50,200), font, font_scale, text_color, font_thickness)
            data='f;'
        
        elif fingers[1] ==1 and fingers[2]==1 and fingers[3]==0 and fingers[4]==0:
            cv2.putText(frame,"left", (50,200), font, font_scale, text_color, font_thickness)
            data='l;'
        elif fingers[1] ==1 and fingers[2]==1 and fingers[3]==1 and fingers[4]==0:
            cv2.putText(frame,"right", (50,200), font, font_scale, text_color, font_thickness)
            data='r;'
        elif fingers[1] ==1 and fingers[2]==1 and fingers[3]==1 and fingers[4]==1:
            cv2.putText(frame,"back", (50,200), font, font_scale, text_color, font_thickness)
            data='b;'
        elif fingers[1] ==0 and fingers[2]==0 and fingers[3]==0 and fingers[4]==0:
            cv2.putText(frame,"stop", (50,200), font, font_scale, text_color, font_thickness)
            data='s;'
    if data:
        if data!=k:
            conn.send(data.encode())
            print(data)
            k=data

    cv2.imshow("JUST FOR SHOWING",frame)
    if cv2.waitKey(1)==ord("q"):
        break

vid.release()
cv2.destroyAllWindows()  
