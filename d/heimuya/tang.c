inherit ROOM;                           
      
void create()
{
        set("short", "令牌堂");
        set("long", @LONG
这里是黑木崖的第三大堂青龙堂的令牌室。室内青砖铺地。桌上
有一盒子(box1)。
LONG );
        set("exits", ([        
            "west"      : __DIR__"qing",
        ]));
        set("item_desc", ([
            "box1": "这是个放令牌的盒子，不过以被人打开，空空如也 。\n",
               ]) );
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}