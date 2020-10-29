//room: didao1.c
inherit ROOM;

void create()
{
  set("short","秘道");
        set("long", @LONG
这是一条异常幽静的走廊，四周漆黑一团，你好象什么都看不见
似的走在里面，你不觉想到这似乎在每个角落都藏着无限杀机，太恐
怖了，四周毫无声息，好象掉下一根针都可能听到。墙上有一个凸起，
象是一个机关(button)。
LONG );

  set("exits",([
      "east" : __DIR__"didao2",
      "west" : __DIR__"didao1",
      "south" : __DIR__"didao5",
  ]));
        set("item_desc", ([
            "button" : "这是一个石头上雕刻出来的图像，凸起着令人感觉有点异样，似乎可以按动(push)。\n",
        ]));

  set("no_clean_up", 0);
  setup();
}
void init()
{
        add_action("do_push","push");
        add_action("do_push","an");
}

int do_push(string arg)
{

        object me = this_player();
        object room;

        if ((arg != "button") || !arg)
        {
                write("你要按什么？\n");
                return 1;
        }

        if( query("str", me)<12 )
        {
                write("你臂力还按不动什么！\n");
                return 1;
        }

        if(!( room = find_object(__DIR__"huoting")) )
                room = load_object(__DIR__"huoting");

        if (!query("exits/out"))
        {
                set("exits/out", __DIR__"huoting");
                message_vision("$N按下了机关，只见侧墙打开，几线亮光透射进来。\n",me);
                set("exits/down", __DIR__"didao1", room);
                message("vision", "侧墙传来一阵嘎嘎声响，露出一个黑黝黝的洞口。\n", room);
        }
        else
        {
                delete("exits/out");
                message_vision("很快机关又变回了原样。洞口又被封住了。\n",me);
                delete("exits/down", room);
                message("vision", "侧墙传来一阵嘎嘎声响，洞口被封住了。\n", room);
        }
        return 1;
}
