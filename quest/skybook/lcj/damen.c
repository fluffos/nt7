// Room: /d/xiangyang/damen.c 大门
// Modify By River 98/10
// Modify By Lklv 2001.9.21
// Modify by tangfeng for 连城诀quest

inherit ROOM;
#include <ansi.h>
#include <wanted.h>

#define QUESTDIR "quest/连城诀/"
#define QUESTDIR1 "quest/连城诀/雪谷激斗篇/"
#define QUESTDIR2 "quest/连城诀/武馆探密篇/"

void create()
{
	set("short", "武馆大门");
	set("long", @LONG
这里是襄阳武馆的大门，两扇黑漆漆的木门向左右敞开着，门口的正上方
高悬着一块黑底金字的大匾，匾上写着四个大字：“襄阳武馆”。门前的台阶
两旁各立着一个石狮，从大门口向里面瞧去，武馆的院子里人来人往，看起来
好象都很忙碌。大门旁边站着一个门卫，脸上神情威严。
LONG
        );
	set("outdoors","武馆");
	set("no_fight", 1);
	set("exits", ([
		"south" : __DIR__"eroad1",
		"enter": "/d/wuguan/menlang",
	]));
	set("objects", ([
                "/d/wuguan/npc/menwei" : 1,
//                "/tmp/ciwei/menwei" : 1,
	]));
	set("incity",1);
	setup();
}

int valid_leave(object me,string dir)
{
	object *obj;
	int x;

	if ( me->query_temp( "wg_help" ) || me->query_temp( "wg_road" ) == 2 )
		return notify_fail("武馆门卫说道：" + RANK_D->query_respect(me) +
			"还是再耐心等一会吧，说不定马上就有人来仗义帮助。\n");
	if ( me->query_temp( "wg_juanzeng" ) )
		me->delete_temp( "wg_juanzeng" );
	if ( me->query_temp( "wg_road" ) == 1 )
		me->delete_temp( "wg_road" );
	if ( dir == "enter" && !wizardp(me)) {
		if ( is_wanted(me) )
			return 0;
		if ( me->query("combat_exp") > 3000 )
		{
			if(!me->query(QUESTDIR1+"over") || me->query(QUESTDIR2+"over"))
				return notify_fail("门卫上前把手一伸：你的武功够高了，在武馆学不到什么了。\n");
			if(me->query_temp(QUESTDIR2+"start"))
			{
				message_vision(HIY"\n门卫疑惑地看着$N道：$N刚才怎么进去又出来了？\n", me);
				me->delete_temp("quest/busy");//
				me->delete_temp("quest/连城诀");
				return notify_fail("门卫上前把手一伸：那有这么好的事情，在武馆进进出出。\n");
			}
			obj = users();
			x = sizeof(obj);
			while(x--)
			{
				if ( obj[x]->query_temp(QUESTDIR2+"start") && obj[x]!=me ) 
					return notify_fail("门卫上前把手一伸："+obj[x]->query("name")+RANK_D->query_respect(obj[x]) +"已经去武馆探密去了，你再等等！");		  
			}
		}
	}
	if ( dir == "enter" && me->query(QUESTDIR1+"over")&& !me->query(QUESTDIR2+"over"))
	{
		message_vision(HIY"\n$N低头似乎和门卫说了些什么。门卫啊地一声叫了出来。\n", me);
		if(me->query(QUESTDIR+"time")&&time()-me->query(QUESTDIR+"time")<86400)
			return notify_fail("门卫上前把手一伸：不管怎样，今天很忙了，"+RANK_D->query_respect(me) +"先行休息去吧！");		  
		if(me->query(QUESTDIR+"combat_exp")&&me->query("combat_exp")-me->query(QUESTDIR+"combat_exp")<500000)
			return notify_fail("门卫上前把手一伸：以"+RANK_D->query_respect(me) +"目前的经验就算进去，也做不了什么，还是抓紧练功吧！");

		message_vision(HIY"门卫啊地一声跳了起来。\n", me);
		message_vision(HIY"只见门卫往旁边一闪。$N从门缝里挤了进去。\n", me);
		me->set(QUESTDIR+"time",time());
		me->set(QUESTDIR+"combat_exp",me->query("combat_exp")); 
		me->set(QUESTDIR2+"start",1);//开始
		me->set_temp(QUESTDIR2+"start",1);
		me->set_temp("quest/busy",1);
	}
	return ::valid_leave(me, dir);
}
