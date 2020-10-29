inherit ROOM;

void create()
{
        set("short", "兵器房");
        set("long", @LONG
这里是天龙寺的兵器房，天龙寺的武功一向是以空手为主，但是
房中仍然准备有一些兵器供刚入门的弟子使用。墙边的兵器架(jia)上放着
各式各样的兵器，可以根据自己喜好，选趁手的。
LONG);
        set("exits", ([
           "west" : __DIR__"cby",
        ]));
 set("item_desc", ([ 
"jia" : "兵器架放着各式各样的兵器：
一次只能拿一件。
        钢剑(jian)           铁甲(armor)        长剑(changjian)
        长鞭(changbian)     竹剑(zhujian)        短剑(duanjian)
        竹剑(zhujian)      

你可以拿(na)一样做你武器。
\n"
]));
	set("coor/x",-330);
  set("coor/y",-280);
   set("coor/z",30);
   setup();

}

void init()
{
	add_action("do_na","na");
}

int do_na(string arg)
{
        mapping fam; 
	object me;
       	me=this_player();
        if (!(fam = this_player()->query("family")) 
            || fam["family_name"] != "天龙寺")
		return notify_fail("你不是天龙寺弟子，不能在这取兵器的！！\n");

	if (me->query_temp("marks/拿1") )
		return notify_fail("你已拿了兵器，还要拿吗？！\n");

	if (arg=="all from jia") 
		return notify_fail("你怎么要拿么多兵器呀，拿去变卖？！\n");

	if (!arg) return notify_fail("你要拿什么兵器？\n");

	if (!"jian from jia"||!"changjian from jia"||!"duanjian from jia"
||!"zhujian from jia"||!"changbian from jian"
||!"armor from jia") return 0;

	if (arg=="jian from jia"){
       	message_vision("$N从兵器架里拿出一把钢剑。\n",me);
	this_player()->set_temp("marks/拿1", 1);
	me = new("/d/city/obj/gangjian");
        me->move(this_player());
	return 1;
	}
	
	if (arg=="changjian from jia"){
       	message_vision("$N从兵器架里拿出一把长剑。\n",me);
	this_player()->set_temp("marks/拿1", 1);
	me = new("/d/city/obj/changjian");
        me->move(this_player());
	return 1;
	}

	if (arg=="duanjian from jia"){
       	message_vision("$N从兵器架里拿出一把短剑。\n",me);
	this_player()->set_temp("marks/拿1", 1);
	me = new("/d/city/obj/duanjian");
        me->move(this_player());
	return 1;
	}

	if (arg=="zhujian from jia"){
       	message_vision("$N从兵器架里拿出一把竹剑。\n",me);
	this_player()->set_temp("marks/拿1", 1);
	me = new("/d/village/obj/zhujian");
        me->move(this_player());
	return 1;
	}
	

	if (arg=="changbian from jia"){
       	message_vision("$N从兵器架里拿出一条长鞭。\n",me);
	this_player()->set_temp("marks/拿1", 1);
     me = new("/clone/weapon/changbian");
        me->move(this_player());
	return 1;
	}
	if (arg=="armor from jia"){
       	message_vision("$N从兵器架里拿出一件铁甲。\n",me);
	this_player()->set_temp("marks/拿1", 1);
	me = new("/d/city/obj/tiejia");
        me->move(this_player());
	return 1;
	}
      
        if (arg=="zhubang from jia"){
       	message_vision("$N从兵器架里拿出一件竹棒。\n",me);
	this_player()->set_temp("marks/拿1", 1);
	me = new("/d/city/obj/zhubang");
        me->move(this_player());
	return 1;
	}

        if (arg=="gangzhang from jia"){
       	message_vision("$N从兵器架里拿出一件钢杖。\n",me);
	this_player()->set_temp("marks/拿1", 1);
	me = new("/d/city/obj/gangzhang");
        me->move(this_player());
	return 1;
	}
}

