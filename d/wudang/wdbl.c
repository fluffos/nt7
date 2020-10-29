inherit ROOM;

void create()
{
      set("short", "武当柏林");
        set("long", @LONG
你穿行在一片茂密的柏林中，阴森郁翠，怪石嶙峋，草深没人。
不时地有兔子从你的身边飞跑而过。
LONG );
      set("outdoors", "wudang");
      set("exits", ([
              "northdown": __DIR__"yuzhengong",
              "southup"  : __DIR__"haohanpo",
      ]));
      set("objects", ([
              "/clone/quarry/tu" : 2,
      ]));
        set("coor/x", -370);
        set("coor/y", -210);
        set("coor/z", 50);
        setup();
      replace_program(ROOM);
}