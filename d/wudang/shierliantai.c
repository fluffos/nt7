inherit ROOM;

void create()
{
        set("short", "十二莲台");
        set("long", @LONG
这里是武当绝顶的十二莲台，台与台之间以曲栏相连，雕刻精美，
是远眺的最佳所在。站立此台四眺，宛如身在千叶宝莲之上，千峰万
壑都在脚下。往西可望到七百里外的华山，东望则汉水如练，襄、樊
一带尽收眼底。
LONG );
        set("exits", ([
                "east" : __DIR__"jinding",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("honglian",1);
        set("coor/x", -360);
        set("coor/y", -420);
        set("coor/z", 180);
        setup();
}
void init()
{
      add_action("do_find","find");
}

int do_find()
{
      object obj;
      object me = this_player();

      if( query("jingli", me)<50 )
            return notify_fail("你找得两眼酸痛，都没有发现什么好东西。\n");

      addn("jingli", -10, me);

      if (!query("honglian"))
            return notify_fail("你找了半天，什么都没有找到。\n");

      addn("honglian",-1);
      obj = new("/d/wudang/obj/honglian");
      obj->move(me);
      tell_object(me,"你找了半天，突然发现一颗红色小草，开着一朵极象莲座的小花。\n");
      return 1;
}

void reset()
{
      ::reset();
      set("honglian",1);
}