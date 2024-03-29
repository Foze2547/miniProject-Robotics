import cv2
import mediapipe as mp

mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles
mp_hands = mp.solutions.hands

capture = cv2.VideoCapture(0)
with mp_hands.Hands(
  model_complexity=0,
  min_detection_confidence=0.5,
  min_tracking_confidence=0.5) as hands:
  while capture.isOpened():
    success, image = capture.read()
    if not success:
      print('Ignored empty webcam\'s frame')
      continue
  
    image = cv2.flip(image, 1)
     
    image.flags.writeable = False
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    results = hands.process(image)

    image.flags.writeable = True
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    
    fingerCount = 0

    if results.multi_hand_landmarks:
      for hand_landmarks in results.multi_hand_landmarks:
        handIndex = results.multi_hand_landmarks.index(hand_landmarks)
        handLabel = results.multi_handedness[handIndex].classification[0].label

        handLandmarks = []

        for landmarks in hand_landmarks.landmark:
          handLandmarks.append([landmarks.x, landmarks.y])
        
        if handLabel == "Left" and handLandmarks[4][0] > handLandmarks[3][0]:
          fingerCount = fingerCount + 1
          cv2.putText(image,"Thumb Finger" , (10,70), cv2.FONT_HERSHEY_PLAIN, 1.5,
                        (204, 229, 255), 3)
        elif handLabel == "Right" and handLandmarks[4][0] < handLandmarks[3][0]:
          fingerCount = fingerCount + 1
          cv2.putText(image,"Thumb Finger" , (10,70), cv2.FONT_HERSHEY_PLAIN, 1.5,
                        (204, 229, 255), 3)

        if handLandmarks[8][1] < handLandmarks[6][1]:
          fingerCount = fingerCount + 1
          cv2.putText(image,"Index Finger" , (10,110), cv2.FONT_HERSHEY_PLAIN, 1.5,
                        (255, 51, 153), 3)
        if handLandmarks[12][1] < handLandmarks[10][1]:
          fingerCount = fingerCount + 1
          cv2.putText(image,"Middle Finger" , (10,150), cv2.FONT_HERSHEY_PLAIN, 1.5,
                        (0,255,233), 3)
        if handLandmarks[16][1] < handLandmarks[14][1]:
          fingerCount = fingerCount + 1
          cv2.putText(image,"Ring Finger" , (10,190), cv2.FONT_HERSHEY_PLAIN, 1.5,
                        (97,255,0), 3)
        if handLandmarks[20][1] < handLandmarks[18][1]:
          fingerCount = fingerCount + 1
          cv2.putText(image,"Pinky Finger" , (10,230), cv2.FONT_HERSHEY_PLAIN, 1.5,
                        (255, 0, 0), 3)

        mp_drawing.draw_landmarks(
          image,
          hand_landmarks,
          mp_hands.HAND_CONNECTIONS,
          mp_drawing_styles.get_default_hand_landmarks_style(),
          mp_drawing_styles.get_default_hand_connections_style()
        )
        
        left_hand = False
        right_hand = False
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                if hand_landmarks.landmark[0].x < hand_landmarks.landmark[17].x:
                    right_hand = True
                else:
                    left_hand = True  
        if left_hand and right_hand:
                    cv2.putText(image,"Right Hand and Left" , (10,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                    (0, 0, 0), 3)
        elif right_hand: 
                    cv2.putText(image,"Right Hand" , (10,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                    (0, 0, 0), 3)
        elif left_hand:
                    cv2.putText(image,"Left Hand" , (10,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                    (0, 0, 0), 3)
        
        # 2 Hand
      if fingerCount == 4:
            # 45 องศาเปิดเข้า
            if  (handLabel == "Left" and handLandmarks[4][0] > handLandmarks[3][0]) or handLabel == "Right" and handLandmarks[4][0] < handLandmarks[3][0]:
                if  handLandmarks[8][1] < handLandmarks[6][1]:
                    if left_hand and right_hand:
                        cv2.putText(image,"Half Open(in)" , (470,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                          (0, 0, 0), 3)
            # 90 องศาเปิดออก
            if  (handLabel == "Left" and handLandmarks[4][0] > handLandmarks[3][0]) or handLabel == "Right" and handLandmarks[4][0] < handLandmarks[3][0]:
                if  handLandmarks[20][1] < handLandmarks[18][1]:
                    if (left_hand and right_hand):
                        cv2.putText(image,"Open All(out)" , (470,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                          (0, 0, 0), 3)
            # 45 องศาเปิดออก
            if handLandmarks[8][1] < handLandmarks[6][1]:
                if handLandmarks[20][1] < handLandmarks[18][1]:
                    if (left_hand and right_hand):
                        cv2.putText(image,"Half Open(out)" , (450,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                          (0, 0, 0), 3)
      #90 องศาเปิดเข้า
      if fingerCount == 10:
          if (left_hand and right_hand):
              cv2.putText(image,"Open All(in)" , (490,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                          (0, 0, 0), 3)
      #ปิด
      if fingerCount == 2:
        if handLandmarks[8][1] < handLandmarks[6][1]:
          if (left_hand and right_hand):
              cv2.putText(image,"Close" , (560,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                          (0, 0, 0), 3)                  
        # 1 Hand
      if fingerCount == 2:
           # 45 องศาเปิดเข้า
           if  (handLabel == "Left" and handLandmarks[4][0] > handLandmarks[3][0]) or handLabel == "Right" and handLandmarks[4][0] < handLandmarks[3][0]:
                if  handLandmarks[8][1] < handLandmarks[6][1]:
                    if not (left_hand and right_hand):
                        if  right_hand:
                            cv2.putText(image,"Half Open(in)" , (470,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
                        elif left_hand:
                            cv2.putText(image,"Half Open(in)" , (470,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)  
           # 90 องศาเปิดออก             
           if  (handLabel == "Left" and handLandmarks[4][0] > handLandmarks[3][0]) or handLabel == "Right" and handLandmarks[4][0] < handLandmarks[3][0]:
                if  handLandmarks[20][1] < handLandmarks[18][1]:
                    if not (left_hand and right_hand):
                        if  right_hand:
                            cv2.putText(image,"Open All(out)" , (470,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
                        elif left_hand:
                            cv2.putText(image,"Open All(out)" , (470,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
           # 45 องศาเปิดออก
           if handLandmarks[8][1] < handLandmarks[6][1]:
                if handLandmarks[20][1] < handLandmarks[18][1]:
                    if not (left_hand and right_hand):
                        if  right_hand:
                            cv2.putText(image,"Half Open(out)" , (450,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
                        elif left_hand:
                            cv2.putText(image,"Half Open(out)" , (450,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
      #90 องศาเปิดเข้า
      if fingerCount == 5:
          if not (left_hand and right_hand):
                        if  right_hand:
                            cv2.putText(image,"Open All(in)" , (490,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
                        elif left_hand:
                            cv2.putText(image,"Open All(in)" , (490,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
      #ปิด
      if fingerCount == 1:
        if handLandmarks[8][1] < handLandmarks[6][1]:
          if not (left_hand and right_hand):
                        if  right_hand:
                            cv2.putText(image,"Close" , (560,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
                        elif left_hand:
                            cv2.putText(image,"Close" , (560,30), cv2.FONT_HERSHEY_PLAIN, 1.5,
                            (0, 0, 0), 3)
    cv2.putText(image, str(fingerCount), (50,450), cv2.FONT_HERSHEY_COMPLEX_SMALL, 3, (153, 21, 255), 7)
    cv2.imshow('RoBoTiC Group',image)
    if cv2.waitKey(1) == 27:
        break
  capture.release()
