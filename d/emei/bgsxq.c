inherit ROOM;

void create()
{
      set("short", "西墙");
        set("long", @LONG
这里是峨眉山报国寺的西墙。寺院里的钟声从墙那边飘来，在空
气中回响。一条山溪从西面山上的解脱桥下流经这里，向山下淌去。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "east"      : __DIR__"bgs",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -380);
        set("coor/y", -220);
        set("coor/z", 10);
        setup();
      replace_program(ROOM);
}