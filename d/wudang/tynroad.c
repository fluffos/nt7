inherit ROOM;

void create()
{
        set("short", "桃园小路");
        set("long", @LONG
眼前豁然开朗，你轻松地走在桃园边的小路上。路上落英缤纷，
一边是桃树林，盛开着粉红的桃花，红云一片，望不到边。还可以看
见蜜蜂「嗡嗡」地在花间飞上飞下忙个不停，间或传来猿猴的叽咋声。
北边是条环山的黄土路。
LONG );
        set("outdoors", "wudang");
        set("exits", ([
                "south" : __DIR__"tyroad8",
        ]));
        set("objects", ([
                "/clone/quarry/hou" : 1
        ]));
        set("coor/x", -310);
        set("coor/y", -300);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}