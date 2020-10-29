// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "卧室"); 
        set("long", @LONG
这里是圆月山庄的卧室。屋子不大，也没什么摆设，乱七八糟扔
着些破破烂烂的旧衣物，墙角布满了蜘蛛网，满屋子都是灰尘，呛的
你不住咳嗽。
LONG );
        set("type","indoors");
        set("sleep_room", 1);
        set("no_fight", 1); 
        set("exits",([
                "east":__DIR__"grass4",
                "south":__DIR__"grass1",
        ]) ); 

        set("coor/x",-600);
        set("coor/y",250);
        set("coor/z",80);
        setup();
        replace_program(ROOM);
}      
