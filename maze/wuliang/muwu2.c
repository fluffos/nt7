// Modify By River 98/12
inherit ROOM;
void create()
{
	set("short", "石屋");
	set("long", @LONG
眼前是一个石屋。这石屋模样甚是奇怪，以一块千百斤重的大石砌成，凹
凹凸凸，宛然是一座小山，洞口被一块花岗巨岩（yan)封住，岩边到处露出空
隙，有的只两三寸宽，有的却有尺宽。?
LONG
	);
        set("outdoors", "大理");

	set("exits", ([
		"south" : __DIR__"muwu1",
	]));

        set("item_desc", ([
            "yan" : "这是一块特别大的岩石，堵住了门口，使人无法进入屋内。\n",
        ]));

        setup();
}

void init()
{
        add_action("do_tui", "tui");
        add_action("do_tui", "push");
}

int do_tui(string arg)
{
        int i;
        i=query("neili", this_player());
        if( !arg || arg!="yan" ) 
           return notify_fail("你要推什么？\n");        
          message_vision("$N站在门前，把双掌放在岩上，深深的吸了一口气，双臂一发劲，大喝一声“开”。\n", this_player());
        if (i>=800) {
          message_vision("$N只听一阵轰响，大石缓缓的移开了！\n", this_player());
          set("exits/enter", __DIR__"muwu3");
          addn("neili", -800, this_player());
          remove_call_out("close");
          call_out("close", 5, this_object());
          }
        else {
          message_vision("$N却见大石纹丝不动，看来$N的内力还不够。\n", this_player());
          set("neili", 0, this_player());
          }
    return 1;
}

void close(object room)
{
         message("vision","大石缓缓移动，把石屋再次封住了。\n", room);
         delete("exits/enter", room);
}