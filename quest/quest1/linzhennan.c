// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// linzhennan.c 林震南   

inherit NPC; 
#include <ansi.h>  
#include "biao.h"

mixed ask_biaodui();
mixed ask_yunbiao();
int   ask_fuwei();
int   ask_yuantu();
int   ask_pixie();
int   ask_tong();

void create()
{
        set_name("林震南", ({ "lin zhennan", "lin"}));
        set("gender", "男性");
        set("age", 65);
        set("title", "福威镖局总镖头");
        set("long", "他就是福威镖局总镖头－－林震南。\n");
        set("combat_exp", 30000);
        set("shen_type", 1);
        set("max_neili", 500);
        set("neili", 500);
        set("jiali", 10);
        
        set_skill("force", 140);
        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set("inquiry", ([     
                "运镖"     : (: ask_yunbiao :),
                "镖队"     : (: ask_biaodui :),  
                "镖"       : (: ask_yunbiao :),
                "向阳老宅" : "林震南说道：那是我从前在福建时住的家院，已经破败了。\n",
                "福威镖局" : (: ask_fuwei :),
                "远图公"   : (: ask_yuantu :),
                "林远图"   : "林震南大怒：小孩子这么没礼貌，直呼先人名讳！\n",
                "辟邪剑法" : (: ask_pixie:),
                "铜钱"     : (: ask_tong:),
                "铜板"     : (: ask_tong:),
        ]));
        set_temp("apply/attack", 500);
        set_temp("apply/defense", 500);
        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

int ask_fuwei()
{
         say("林震南炫耀地说：我们林家三代走镖，一来仗着先祖远图公当年闯下的威名，二\n"
                 "来靠著我们林家家传的玩艺儿不算含糊，这才有今日的局面，成为大江以南首屈\n"
            "一指的大镖局。江湖上提到『福威镖局』四字，谁都要翘起大拇指，说一声：『\n"
            "好福气！好威风！』哈哈，哈哈！\n");
         set_temp("marks/林1", 1, this_player());
         return 1;
}

int ask_yuantu()
{
          if( query_temp("marks/林1", this_player()) )
          {
                 say("林震南磕一磕烟斗，说道：远图公是我的祖父，福威镖局是他一手创办的。当年\n"
                        "祖父以七十二路辟邪剑法开创镖局，当真是打遍黑道无敌手。其时白道上英雄见\n"
                          "他太过威风，也有去找他比试武艺的，青城派掌门余观主的师父长青子少年之时\n"
                        "便在他辟邪剑法下输了几招。\n");
                 set_temp("marks/林2", 1, this_player());
                 return 1;
          }
          else 
          {
                 say("林震南说道：远图公是我的祖父。\n");
                 return 1;
          }
}

int ask_pixie()
{
          int p1, p2, p3, p4;
          if( query("passwd", this_player()) )
          {
                 say("林震南不悦地说道：我不是都告诉你了吗？我的剑法不及先祖。\n");
          }
          else if( query_temp("marks/林2", this_player()) )
          {
                 say("林震南一惊，说道：你怎么知道的？噢，我刚才说露嘴了。嗨，在下的功夫外人\n"
                          "不知底细，其实及不上先祖。。\n");
                 write("林震南顿一顿，接着对你低声说：先祖去世前，曾给家父留下");
                 p1 = random(4) + 1;
                 p2 = random(4) + 1;
                 p3 = random(4) + 1;
                 p4 = random(4) + 1;
                 set("passwd", p1*1000+p2*100+p3*10+p4, this_player());
                 write(CHINESE_D->chinese_number(p1) + "千" + CHINESE_D->chinese_number(p2) +
                             "百" + CHINESE_D->chinese_number(p3) + "十" + CHINESE_D->chinese_number(p4));
                 write("个\n铜钱，我一直未解其中奥秘。\n");
          }
          else 
          {
                   message("vision",
                           HIM "林震南勃然大怒，喝道：你也窥视我们林家的辟邪剑谱？！我跟你拼了！\n" NOR, 
                           environment(), this_object());
                   kill_ob(this_player());
          }
          delete_temp("marks/林1", this_player());
          delete_temp("marks/林2", this_player());
          return 1;
}

int ask_tong()
{
          int p, p1, p2, p3, p4;
          if( !(p=query("passwd", this_player())) )
          {
                 say("林震南一脸讥笑的样子，说：怎么混到这一步了到处要钱？\n");
          }
          else 
          {
                 write("林震南低声说：先祖去世前，曾给家父留下");
                 p1 = (int)p / 1000;
                 p2 = (int)(p - p1 * 1000) / 100;
                 p3 = (int)(p - p1 * 1000 - p2 * 100) / 10;
                 p4 = (int)(p - p1 * 1000 - p2 * 100 - p3 * 10);
                 write(CHINESE_D->chinese_number(p1) + "千" + CHINESE_D->chinese_number(p2) +
                             "百" + CHINESE_D->chinese_number(p3) + "十" + CHINESE_D->chinese_number(p4));
                 write("个\n铜钱，我一直未解其中奥秘。\n");
          }
          return 1;
}

string chinese_time(int t)
{
        int d, h, m, s;
        string time;
        s = t % 60;     t /= 60;
        m = t % 60;     t /= 60;
        h = t % 24;     t /= 24;
        d = t;
        if (d) time = chinese_number(d) + "天";
        else time = "";
        if (h) time += chinese_number(h) + "小时";
        if (m) time += chinese_number(m) + "分";    
        time += chinese_number(s) + "秒";
        return time;
}

mixed ask_yunbiao()
{
        int time;
        object me, biaoche;
        mapping biao;

        me = this_player();

        if( query("combat_exp", me) < 100000 )
                return "运镖可是件危险的差使，还是练好了功夫再来吧！\n";    

        if( query("combat_exp", me) > 10000000000 )
                return "让您来运镖太委屈您了！\n";    
                      
        if( query_temp("quest_yunbiao/have_task", me) )
                return "你上次的镖还没送到呢，怎么又来了？\n"; 

        if( me->query_condition("yunbiao_busy") )
                return "你刚运镖失败，还是等待一段时间再来吧！\n"; 

        if( query_temp("quest_yunbiao/finished_time", me )
        &&  (time()-query_temp("quest_yunbiao/finished_time", me))<5 )
                return RANK_D->query_respect(me) + "辛苦了，现在没有镖车要运，过会再来吧！\n";

        if( mapp(query_temp("quest_yunbiao", me) )
        &&  !query_temp("quest_yunbiao/finished_time", me )
        &&  (time()-query_temp("quest_yunbiao/start_time", me))<60 )
                       return "你把我的镖弄哪里去啦？不是被人劫了吧？\n";

        biao = yun_biao[random(sizeof(yun_biao))];
        time = biao["time"];
            
        delete_temp("quest_yunbiao", me);
        set_temp("quest_yunbiao/name", biao["name"], me);
        set_temp("quest_yunbiao/file", biao["file"], me);
        set_temp("quest_yunbiao/bonus", biao["bonus"], me);
        set_temp("quest_yunbiao/time", biao["time"], me);
        set_temp("quest_yunbiao/start_time", time(), me);
        set_temp("quest_yunbiao/have_task", 1, me);

        biaoche = new(__DIR__"biaoche");
        set("time", time, biaoche);
        set("file", biao["file"], biaoche);
        biaoche->start_escape_me();
        set("owner",query("id",  me), biaoche);
        set("owner_name",query("name",  me), biaoche);
        biaoche->move(environment(me));
            
        /*
        message("channel:rumor",HIM"【镖局】"+query("name", me)+
                     "即将护送镖车起程前往" + biao["name"] + "！\n" NOR,
                     users());  
        */
        
        delete_temp("apply/short", me);
        set_temp("apply/short",
                            ({HIM"福威镖局镖头"NOR+me->name()+"("+query("id", me)+")"}), me);

        message_sort(HIM "$N" HIM "对$n" HIM "吩咐道：请在" + chinese_time(time) + "内，将镖车运送到" +
                     biao["name"] + "。一路多加小心，你还是趁早上路吧！\n" NOR, this_object(), me);
        return 1;
}


mixed ask_biaodui()
{
            int time, i;
            object me, parter, biaoche, *team;
            mapping biao;

            me = this_player();

            if( query("combat_exp", me) < 200000 )
                      return "运镖可是件危险的差使，还是练好了功夫再来吧！\n";
                      
            if (! pointerp(team = me->query_team()))
                       return "镖队需要人多一点才有保障，多叫些人手来吧！\n";

            i = sizeof(team);
            if (i > 2) return "人多手杂，容易坏事！\n";

            if (objectp(team[0]) && objectp(team[1]))
            {
                     if(team[0] == me) parter = team[1];
                     else parter = team[0];
            }

            if (! objectp(parter) 
         || !present(query("id", parter),environment(me)) )
                       return "还是约上你的同伴一起来吧！\n";

            if( query_temp("quest_yunbiao/have_task", me) )
                       return "你们上次的镖还没送到呢，怎么又来了？\n";

            if( mapp(query_temp("quest_yunbiao", me) )
         && !query_temp("quest_yunbiao/finished_time", me )
         && (time()-query_temp("quest_yunbiao/start_time", me))<60 )
                       return "你把我的镖队弄丢了，居然还有脸回来见我？\n";

        if( query("combat_exp", parter)<50000 )
                      return "运镖可是件危险的差使，不要让你的同伴去送死了！\n";

         if( query("combat_exp", me) > 10000000000 ) 
                    return "让您来运镖太委屈您了！\n";     

          if( query("combat_exp", parter) > 10000000000 ) 
                    return "让您的同伴和你一起运镖太委屈他了！\n";     
                      
        if( me->query_condition("yunbiao_busy") )
                return "你刚运镖失败，还是等待一段时间再来吧！\n"; 

        if( parter->query_condition("yunbiao_busy") )
                return "你的同伴刚运镖失败，还是等待一段时间再来吧！\n"; 

            if( mapp(query_temp("quest_yunbiao", parter) )
         && !query_temp("quest_yunbiao/finished_time", parter )
         && (time()-query_temp("quest_yunbiao/start_time", me))<60 )
                       return "你找这样无能的同伴当帮手，我可不放心把镖队交给你！\n";

            biao = yun_biao[random(sizeof(yun_biao))];
            time = biao["time"];
            
            delete_temp("quest_yunbiao", me);
            set_temp("quest_yunbiao/name", biao["name"], me);
            set_temp("quest_yunbiao/file", biao["file"], me);
            set_temp("quest_yunbiao/bonus", biao["bonus"], me);
            set_temp("quest_yunbiao/time", biao["time"], me);
            set_temp("quest_yunbiao/start_time", time(), me);
            set_temp("quest_yunbiao/have_task", 1, me);

        delete_temp("quest_yunbiao", parter);
            set_temp("quest_yunbiao/name", biao["name"], parter);
            set_temp("quest_yunbiao/file", biao["file"], parter);
            set_temp("quest_yunbiao/bonus", biao["bonus"], parter);
            set_temp("quest_yunbiao/time", biao["time"], parter);
            set_temp("quest_yunbiao/start_time", time(), parter);
            set_temp("quest_yunbiao/have_task", 1, parter);

            biaoche = new(__DIR__"da_biaoche");
            set("time", time, biaoche);
            set("file", biao["file"], biaoche);
            biaoche->start_escape_me();
            set("owner",query("id",  me), biaoche);
            set("parter",query("id",  parter), biaoche);
            set("owner_name",query("name",  me), biaoche);
            biaoche->move(environment(me));

        /*
            message("channel:rumor",HIM"【镖局】"+query("name", me)+
                     "率领的镖队即将起程前往" + biao["name"] + "！\n" NOR, users());
        */
        
            delete_temp("apply/short", me);
            set_temp("apply/short",
                         ({HIM"福威镖局镖头"NOR+me->name()+"("+query("id", me)+")"}),me);

            delete_temp("apply/short", parter);
            set_temp("apply/short",
                             ({HIM"福威镖局镖师"NOR+parter->name()+"("+query("id", parter)+")"}),parter);

            message_sort(HIM "$N" HIM "对$n" HIM "吩咐道：请在" + chinese_time(time) + "内，将镖队运送到" +
                     biao["name"] + "。一路多加小心，你们还是趁早上路吧！\n" NOR, this_object(), me);
        return 1;
}

void die()
{
        this_object()->full_self();  
        return; 
}

void unconcious()  
{
        this_object()->full_self();  
        return; 
}
