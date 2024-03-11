
class Button{
    public:
        Button(int x,int y,int w,int h,char text[]);
        void change();
        void init();
    private:
        int x;
        int y;
        int w;
        int h;
        char text[32];
};