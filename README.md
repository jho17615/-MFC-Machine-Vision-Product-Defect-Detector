# 머신비전 제품불량 검출기
머신 비전 기술을 활용하여 제품에 발생할 수 있는 시각적 오류를 실시간으로 감지하고 분석하는 통합 솔루션 입니다.

![영상.gif](img%2F%EC%98%81%EC%83%81.gif)

---
# 구성도
![1.png](img%2F1.png)
1.시작: 프로세스의 시작점입니다.

2.카메라 영역설정 (자동): 카메라가 촬영할 영역을 자동으로 설정하는 단계입니다.

3.카메라 설정: 카메라의 세부 설정을 조정하는 단계입니다.

4.패턴데이터 저장: 인식할 패턴에 대한 데이터를 저장하는 단계입니다.

5.패턴인식: 저장된 데이터를 바탕으로 입력된 이미지에서 패턴을 인식하는 단계입니다.

6.결과출력 저장: 패턴 인식의 결과를 저장하는 단계입니다.

7.종료: 프로세스의 종료점입니다.

---

# 화면구성
![그림1.png](img%2F%EA%B7%B8%EB%A6%BC1.png)

------------------

## 1.자동 화면영역 설정

1. 그레이스케일 변환
![2.png](img%2F2.png)
2. 가우시안 블러
![3.png](img%2F3.png)
3. 이진화
![4.png](img%2F4.png)
4. 윤곽선 
![5.png](img%2F5.png)
5. 2번째로 큰 사각형 검출 
![6.png](img%2F6.png)
6. 검출된 사각형 수평 회전 
![7.png](img%2F7.png)
7. 빨간색포인트 찾기
![8.png](img%2F8.png)
8. 화면 수직 기준서기준으로 오른쪽이으면 180도 회전 
![9.png](img%2F9.png)
![10.png](img%2F10.png)
 

9. 최종 사각형 검출 및 추출

![11.png](img%2F11.png)    

 10.  추출 화면
![12.png](img%2F12.png)
---------------------------------------
## 2.패턴인식데이터 저장/삭제
![img_4.png](img_4.png)
![4.1.png](img%2F4.1.png)
---
## 3.패턴매칭 실행
![5.2.png](img%2F5.2.png)
![5.1.png](img%2F5.1.png)
---
## 4.패턴인식데이터 목록
![4.2.png](img%2F4.2.png)
![4.3.png](img%2F4.3.png)
---
## 5.카메라 정밀조작
![6.1.png](img%2F6.1.png)
![6.2.png](img%2F6.2.png)
---
## 6.카메라 프리셋
![8.6.png](img%2F8.6.png)
![7.1 (2).png](img%2F7.1%20%282%29.png)
![7.1 (1).png](img%2F7.1%20%281%29.png)
![7.2.png](img%2F7.2.png)
![7.3.png](img%2F7.3.png)
----
## 7.결과출력 저장
![s.png](img%2Fs.png)
![a.png](img%2Fa.png)
