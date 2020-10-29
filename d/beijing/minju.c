// Updated by rama

inherit ROOM;
#include <ansi.h>

int do_open(string arg);
int do_knock(string arg);

void create() {
        set("short", "民居");
        set("long", @LONG
这里是一件普普通通的民居，全屋只有屋角摆着一张床(chuang)，
其它的什么也没有。
LONG );
        set("outdoors", "beijing");
        set("no_clean_up", 0);
        set("exits", ([
                "east" : "/d/beijing/shi_1",
        ]));
        set("item_desc", ([
                "chuang" : "木板作成的小床，但是没有一丝尘埃。\n" ,
        ]));

	set("coor/x", -2840);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
}
void init()
{
        add_action("do_knock", "knock");
        add_action("do_open","open");
}
int do_open(string arg)
{
        if(arg=="chuang")
        return notify_fail("你用力拉了拉床板，结果一点动静都没有！\n");
        else return 0;
}

int do_knock(string arg)
{
        object me;
        me = this_player();
        if (!arg||arg=="") 
                return notify_fail("你要敲什么？\n");
          if (arg != "chuang")
                return notify_fail("你要敲什么？\n");
          if( arg=="chuang" ) {
                message_vision("$N试著敲了敲床板。\n", me);
                if( query("bunch/bunch_name", me) == "修罗门" )
                {
                        message_vision(HIB"床板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“原来是自家兄弟啊！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move("/d/beijing/xlm_bjfb");
                        return 1;
                }
                if( query("bunch/bunch_name", me) != "修罗门" && query("shen", me) <= 0 )
                {
                        message_vision(HIB"床板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“是来投靠咱们修罗门的吧！”，
说完一把把$N拉了进去。\n"NOR, me);
                        me->move("/d/beijing/xlm_bjfb");
                        return 1;
                }
                if( good_bunch(me) || query("shen", me)>0 )
                { 
                        message_vision("床板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“你这种人也敢来此，活的不耐烦了么？”\n门被重重的关上了。\n",me);  
                        return 1; 
                } 
                message_vision("门板吱呀一声开了，从里面探出个头来，看了$N两眼说道：“既然是本门的兄弟，就进来吧！”，
说完一把把$N拉了进去。\n",me);
                me->move("/d/beijing/xlm_bjfb"); 
                return 1; 
        }
        
        return 1;
}
  