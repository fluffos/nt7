inherit ROOM;

void create()
{
      set("short", "凌云梯");
        set("long", @LONG
这是凌云梯，最早是一位叫阿婆多的外国和尚在此缚木架石，以
渡行人，又叫「胡僧梯」。路边有梅子坡，可见满坡青梅如豆，于疏
枝密叶中逗引行人，甚有望梅止渴之功用。此梯北通洗象池，南至雷
洞坪。
LONG );
      set("outdoors", "emei");
      set("exits", ([
          "northdown" : __DIR__"xixiangchi",
          "southup"   : __DIR__"leidongping",
      ]));
      set("no_clean_up", 0);
        set("coor/x", -560);
        set("coor/y", -250);
        set("coor/z", 170);
        setup();
      replace_program(ROOM);
}