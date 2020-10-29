//ROOM neishi.c
inherit ROOM;
void init();
int do_move(string);
void create()
{
        set("short", "成德殿后厅");
        set("long", @LONG
这里是日月神教的后厅。看上去满是灰尘，但中间有一个瓷碗 (
wan)，似乎有古怪。
LONG );
        set("exits", ([
                "east" : __DIR__"house1",
                "west" : __DIR__"restroom",
                "south":__DIR__"chengdedian",
        ]));
        set("objects" , ([
             __DIR__"npc/zish" : 4,
        ]));
        set("item_desc", ([
            "wan" : "这是一个自汉代流传下的古董，很别致。\n",
        ]));
//        set("no_clean_up", 0);
        setup();
}
void init()
{
        add_action("do_circle", "circle");
        add_action("do_circle", "zhuan");
}

int do_circle(string arg)
{

        object me = this_player();
        object room;

        if ((arg != "wan") || !arg)
          return notify_fail("你要旋什么？\n");
        if( query("str", me)<12 )
          return notify_fail("你臂力连旋不开什么！\n");
        if(!( room = find_object(__DIR__"didao1")) )
           room = load_object(__DIR__"didao1");
        if(!objectp(room))  return notify_fail("ERROR:not found 'didao1.c' \n");
        if (!query("exits/down"))
          {
          set("exits/down", __DIR__"didao1");
          message_vision("$N将碗旋开，见侧墙打开露，出一个黑幽幽的洞口.\n",me);                    
         set("exits/out", __DIR__"huoting", room);
         return notify_fail("一定要抓紧时间，走后将它关上。\n");
        }
        if(!( room = find_object(__DIR__"didao1")) )
           room = load_object(__DIR__"didao1");
        if(!objectp(room))  return notify_fail("ERROR:not found 'didao1.c' \n");
        if (!query("exits/down"))
          {
          set("exits/down", __DIR__"didao1");
          message_vision("$N旋动了碗，只见侧墙打开，露出一个黑幽幽
              的洞口。\n",me);
          set("exits/out", __DIR__"huoting", room);
          message("vision", "外面传来一阵搬动碗的声音，一束光线射了进来。
          \n", room);
          }
         else
          {
          delete("exits/down");
          message_vision("很快碗又搬回了原位。侧墙上的洞口又被封住了。\n",me);
          delete("exits/out", room);
          message("vision", "外面传来一阵搬动碗的声音，洞口被封住了。\n", room);
          }
       return 1;
}