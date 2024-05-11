Giới thiệu chung: dự án Game "Into the space" làm bằng 100% ngôn ngữ C++ 
kết hợp thư viện đồ hoạ SDL2. Thể loại: endless runner
Cách chơi:
    +Bạn điều khiển 1 phi thuyền với nhiệm vụ là sống sót lâu nhất có thể trong không gian
     có cách thiên thạch bay ngẫu nhiên từ mọi phía.
    +Arrow up: di chuyển phi thuyền về phía trước.
    +Arrow right: xoay phi thuyền sang phải.
    +Arrow left: xoay phi thuyền sang trái.
    +Space: bắn đạn
Chạy code trong thư mục Project với: make 
(hoặc g++ -std=c++17 -o main.exe Src/*.cpp -IHeaderFile -ISDL2/include -LSDL2/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf)
