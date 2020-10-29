// This program is a part of NITAN MudLIB

inherit ROOM;

void create()
{
        set("short", "富贵如意厅"); 
        set("long", @LONG
这是圆月山庄的正厅『富贵如意厅』，房子很大，建筑也很堂皇，
如果摆酒席可以放下十几张桌子，但令人奇怪的是，偌大一间屋子，
除了一张偌大的床以外，便什么也没有了，而那张床简直比厨房里的
锅子还油腻，似乎无论往什么地方随手一摸，总会摸出一两块吃剩的
肉，三四根还没啃完的肉骨头，更为恼人的是，只见时不时有几只老
鼠上蹿下跳，整间屋子散发着一种夹杂着浓郁酒气的怪味。
LONG );
        set("type","house");
        set("valid_startroom", 1);
        set("indoors", "wansong");
        set("exits",([
                "east":__DIR__"shibanlu2",
                "west":__DIR__"suishilu2",
                "south":__DIR__"suishilu1",
                "north":__DIR__"shibanlu4",
        ]) );
        set("objects",([
                CLASS_D("mojiao") + "/liuruosong" : 1,
        ]) );
/*
        set("item_desc", ([
                "床": "一张偌大的床，又脏又乱，摇摇晃晃的似乎一推就会散架（ｍｏｖｅ）。\n",
                "bed": "一张偌大的床，又脏又乱，摇摇晃晃的似乎一推就会散架（ｍｏｖｅ）。\n",
                "偌大的床": "一张偌大的床，又脏又乱，摇摇晃晃的似乎一推就会散架（ｍｏｖｅ）。\n"
        ]) );
*/
        set("coor/x",-590);
        set("coor/y",220);
        set("coor/z",80);
        setup();
} 

/*
void init()
{
        add_action("do_move", "move");
} 

int do_move(string arg)
{
        object mice;
        if ( !arg && arg != "bed" && arg != "床" && arg != "偌大的床")
                return 0;
        if( query("amount") > 5 )
                return 0;
        message_vision("$N晃了下床，一只小老鼠飞块地蹿了出来．\n", this_player());
        mice = new(__DIR__"obj/mouse");
        if(mice) 
                mice->move(this_object());
        addn("amount",1);
        return 1;
} 

void reset()
{
        ::reset();
        set("amount", 0);
}
*/
