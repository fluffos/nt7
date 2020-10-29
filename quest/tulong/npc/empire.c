inherit NPC;
#include <ansi.h> 
int ask_me();
int cure_lighting(); 
int kill_lighting(); 
void create()
{
        set_name(HIY"夜"+HIG"辰"NOR, ({ "night" }) );
        set("gender", "女性"); 
        set("title", HIC"精灵之王"NOR);
        set("age", 20);
        set("long",@LONG
她就是精灵界之主，世间所有精灵的帝王。她的背后有一对透明的羽
翼，散发着晶亮的光芒。在她的手中，拿着一把薄薄的透明的长刀。
那就是精灵界的宝物——精灵刀。她微微漂浮在空中，虽然并没有逼
人的气势，但却自有一种无上的威严。
LONG);        
        set("str", 18);
        set("con", 52);
        set("dex", 100); 
        set("per", 100);
        set("max_qi", 50100);
        set("max_jing", 50100); 
        set("neili", 50010);
        set("max_neili", 50010);
        set("attitude", "peaceful"); 
        set_skill("dodge", 1400); 
        set_skill("blade", 1300); 
        set_skill("parry", 1300); 
        set_skill("force", 1300);  
        set_skill("music", 1300);
        set_skill("spirit-dodge", 1300); 
        set_skill("spirit-blade", 1300); 
        map_skill("dodge", "spirit-dodge");
        map_skill("blade", "spirit-blade");
        map_skill("parry", "spirit-blade"); 
        set("chat_chance_combat", random(20)+30); 
      set("inquiry", ([
            "恢复" : (: ask_me :),
        ]) );
        set("chat_msg_combat", ({
               (: cure_lighting :), 
         }) );

                set("combat_exp", 20010000+random(20110000));
        
        set_temp("apply/attack", 360+random(500));
        set_temp("apply/damage",500+random(500));
        set_temp("apply/armor", 500+random(500));

        setup(); 
        carry_object("/quest/tulong/obj/book");
 } 
void init()
{ 
       add_action("do_kill","hit");
       add_action("do_kill","kill");
} 

int do_kill(string arg)
{   
    object me, ob; 
    string callname;
    ob=this_player();
    me=this_object();

        callname = RANK_D->query_rude(me);
        if (random(3) > 1)
        message_vision("\n$N对著$n喝道：「" 
                + callname + "！今日不是你死就是我活！」\n\n", ob, me);
        else
        message_vision("\n$N对著$n喝道：「" 
                + callname + "！明年今日就是你的忌日！」\n\n", ob, me); 

       call_out("kill_player",1); 

        return 1;
}

int ask_me()
{ 
       object me = this_player();

       if( query_temp("m_success/鱼怪", me)){remove_call_out("cure_lighting");
 
       command("smile"); 
       command("say 你拯救过我的人民，我应该给你补偿。");
       call_out("cure_lighting",3); 

       return 1;
       } 
       command("?"+query("id", me));
       return 1;
}
 
int kill_player()
{
    object me, ob;
    ob=this_player();
    me=this_object();

        me->command("sigh");
        me->command("say 你这又何苦？"); 
        me->command("getblade");
        me->command("wield blade");
        me->set("chat_msg_combat",({
               (: kill_lighting :), 
         }) );
         remove_call_out("kill_ob");
        call_out("kill_ob", 1, ob);
        return 1;
}
int cure_lighting()
{
remove_call_out("curing");
message_vision( HIY "\n\n夜"+HIG"辰"+HIC"忽地展开背后的羽翼，飞到半空，身周散发出柔和的光芒！！\n\n" NOR,
this_object());
call_out("curing",random(1)+1);

        return 1;
} 

int curing()
{ 
        int fw;
        object me = this_object();
        int i;
        int dam;
        object *inv;
        message_vision( HIY "\n\n夜"+HIG"辰"+HIC"双手环于胸前，光芒缓缓撒下！！！\n\n",this_object()); 
                fw = (int)me->max_food_capacity();
                set("food", fw, me);
                fw = (int)me->max_water_capacity();
                set("water", fw, me);
                set("jing",query("max_jing",  me), me);
                set("eff_jing",query("max_jing",  me), me);
                set("qi",query("max_qi",  me), me);
                set("eff_qi",query("max_qi",  me), me);
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
        dam = random(200)+200;
        if(dam <0) dam = 0;
        inv[i]->receive_curing("qi",dam); 
        inv[i]->receive_heal("qi",dam);
  tell_object(inv[i], HIG "你沐浴在光芒里，觉得自己被恢复了！\n"NOR);
         }
        return 1;
}  
int kill_lighting()
{
remove_call_out("hurting");
message_vision( HIY "\n\n夜"+HIG"辰"+HIC"忽地展开背后的羽翼，飞到半空，双手耀出一团光芒！！\n\n" NOR,
this_object());
call_out("hurting",random(1)+1);


        return 1;
}

int hurting()
{
        int i;
        int dam;
        object *inv;
        message_vision( HIY "\n\n夜"+HIG"辰"+HIC"双手结印，霎时间光芒大盛，天地间只剩一片耀目的光芒！！！\n\n",this_object());
        inv = all_inventory(environment(this_object()));
        for(i=sizeof(inv)-1; i>=0; i--)
        if( living(inv[i]))
        if( inv[i] != this_object())
        {
        dam = random(200)+100;
        if(dam <0) dam = 0;
        inv[i]->receive_wound("qi",dam);
        COMBAT_D->report_status(inv[i],1);
        }
        return 1;
}
