//room: house1.c
//Updated by haiyan

inherit ROOM;

void create()
{
     set("short","内室");
        set("long", @LONG
这是一个精雅的小舍，一进门便可闻到一阵浓冽的花香。房中挂
着一幅五女向凤图，图中绘着五个宫装美女，美目盼兮，艳丽脱俗。
屋里还有一张茶几(teapoy)，几张椅子，椅子上铺着绣花锦垫，西面
有一扇洞形门通向后厅。
LONG );

     set("exits",([
         "west" : __DIR__"huoting",
     ]));

     set("valid_startroom", 1);
     set("item_desc", ([
         "teapoy": "这张茶几似乎曾经给人移动过。\n",
     ]));

     setup();
}

void init()
{
     add_action("do_move", "move");
     add_action("do_move", "push");
}

void close_path()
{
     if (! query("exits/enter"))   return;
     message("vision","茶几又自动移了回来，盖住了入口。\n", this_object());
     delete("exits/enter");
}

int do_move(string arg)
{
     if (! arg || arg != "teapoy" )
        return notify_fail("什么？\n");
     else
     {
        write("你把茶几推开，露出了一个通道。\n");
        if (! query("exits/enter"))
        {
            set("exits/enter", __DIR__ "midao01");
            call_out("close_path", 5);
        }
        return 1;
     }
}