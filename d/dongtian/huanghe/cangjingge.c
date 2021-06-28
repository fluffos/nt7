// This program is a part of NITAN MudLIB 
// redl 2013/9
#include <ansi.h> 
#include <room.h> 
inherit __DIR__"normal.c"; 

#define ENCNUM 16
#define ENCRND 4
#define DELAY_T 1000

int clean_up() { return 1;}

void create()
{
        set("short", "藏经阁");
        set("long", 
"这里是洞天里的藏经阁，天下凡间武学尽集于此。密密麻麻，高及屋顶\n"
"的书架布满四周，几排大书架中间，间隔地放着数丈长的书桌。目光及处，\n"
"能看到桌上放了几本秘笈，和几位正在执经沉迷阅读的武林人士。\n"
);
                //set("outdoors", "yangzhou");
                set("exits",([ /* sizeof() == 1 */
                        "south" : __DIR__"zoulang11",
                ]));

        set("no_steal",1);
        set("no_beg",1);         
                set("no_rideto", 1);
                set("no_flyto", 1);
        set("no_drift", 1);
        set("no_sleep_room", 1);

        set("encounter/SN", random(ENCRND) + 1);
        set("encounter/amount", ENCNUM / 4);
        set("encounter/ntime", time() + DELAY_T + random(DELAY_T / 2));
        setup();
}

void init_encounter(object me)//阵图进入调用
{
        if (query("dongtian/encounter/SN2", me) && query("dongtian/encounter/SN2", me) < (ENCRND + 1)) return;
        set("dongtian/encounter/SN2", random(ENCRND) + 1, me);
}

void add_encounter()//阵图定时调用
{
        if (query("encounter/ntime") > time() || query("encounter/amount") >= ENCNUM) return;
        if (query("hold_time", get_object(__DIR__"guangchang.c")) < 2) return;//是npc的洞天
        set("encounter/ntime", time() + DELAY_T + random(DELAY_T / 2));
        addn("encounter/amount", 1);
        if (query("encounter/amount") >= ENCNUM) {
                CHANNEL_D->channel_broadcast("dt", NOR + HIW + "远望" + NOR + HIC + __DIR__"guangchang.c"->load_name() + NOR + HIW + "洞天的" + query("short") + "方向，宝光充盈气冲云霄。\n" + NOR);
        }
}

void init()
{
        int rnd;
        object ob;
//      object room;
        string obname;
        object me = this_player();
        object gcroom = get_object(__DIR__"guangchang.c");
        int halfamount;
        string *giftobs = ({});

         if (!query("dongtian/encounter/SN2", me))
                init_encounter(me);
        
        if (playerp(me) && 
                ( (query_temp("dongtian/houshan/hold_time", me)==query("hold_time", gcroom) && !gcroom->owner_level(me)) || (query("dongtian/encounter/SN2", me) && query("dongtian/encounter/SN2", me)==query("encounter/SN")) )
                 && query("encounter/amount"))  {       
                halfamount = query("encounter/amount") / 2;
          while (query("encounter/amount")>halfamount) {
        set("encounter/ntime", time() + DELAY_T + random(DELAY_T / 2));
                addn("encounter/amount", -1);
        set("encounter/SN", random(ENCRND) + 1);
                delete("dongtian/encounter/SN2", me);
                init_encounter(me);
                
                //奖励
                ob = new("/d/dongtian/obj/wanxiangbook");
                set("no_open_msg", 1, ob);
                rnd = ob->do_open(query("id", ob));
                
        if (!ob->move(this_object()))
        {
                destruct(ob); 
        } 
        else
        {
                me->start_busy(5 + random(6));//等待被主人抓贼
                        set("who_get/id", query("id", me), ob);
                        set("who_get/time", time() + 90, ob);
                        obname = query("name", ob);
                        message_vision(append_color(
                                NOR + CYN + (random(2) ? "哐啷" : "噹地") + (random(2) ? "~ " : "，") + NOR + CYN + "$N" + (random(2) ? "踩" : "踢") + (random(2) ? "到" : "住") + obname + NOR + CYN + (random(2) ? ".." : "...") + "\n" NOR
                                , CYN), me);
                        //if (rnd < 100) 
                        giftobs += ({obname});
/*                      //if (rnd < 300) {//通知主人方
                                if (objectp(room = get_object(__DIR__"houdian"))) {
                                        tell_room(room, NOR + HIG + "魔像：" + query("name", me) + NOR + HIG + "在本洞天发现了" + obname + NOR + HIG + "。\n" + NOR);
                                }
                                room = get_object(__DIR__"dadian");
                                if (objectp(room)) {
                                        tell_room(room, NOR + HIG + "魔像：" + query("name", me) + NOR + HIG + "在本洞天发现了" + obname + NOR + HIG + "。\n" + NOR);
                                }
                        //}*/
        }
      }
        if(giftobs && sizeof(giftobs)) 
                CHANNEL_D->channel_broadcast("dt", sort_msg(NOR + HIW + "传说有人在" + NOR + HIC + __DIR__"guangchang.c"->load_name() + NOR + HIW + "洞天的" + query("short") + "发现了" + implode(giftobs, NOR + HIW + "、" + NOR + HIW) + NOR + HIW + "。\n" + NOR, 64));
        }

        ::init();
}
