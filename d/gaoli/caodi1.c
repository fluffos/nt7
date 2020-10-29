// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "草地");
        set("long", @LONG        
这里是一片青草地。草地柔软疏松，走在上面非常舒服。四周是绿
林环绕，空气清新，景色秀丽。西边有一座寺院，看起来规模不是很大。
里面传来诵经的声音。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southeast" : __DIR__"suishilu2",
                "west":__DIR__"miaodoor",
               ]));
       setup();
        replace_program(ROOM);
}        
