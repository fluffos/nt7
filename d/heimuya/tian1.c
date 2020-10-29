inherit ROOM;
 
void create()
{
        set("short", "天香堂");
        set("long", @LONG
这里是黑木崖的第四大堂『天香堂』。一中年妇人横眉立在当地。
LONG );
        set("exits", ([
            "northdown"   : __DIR__"dating4",
        ]));
        set("objects", ([
            CLASS_D("riyue") + "/shang": 1,
        ]));       
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}