
#include <ansi.h>
inherit FIGHTER;
#define QUESTDIR "skybook/shediao/风雪惊变/"

void create()
{
        set_name("金兵", ({ "jin bing", "bing" }));
        set("gender", "男性");
        set("long", "这人就是完颜洪烈的护卫金兵。\n");
        set("str", 25);
        set("dex", 25);
        set("con", 25);
        set("int", 25);
        set("per", 25);
        set("shen_type", -1);
        set("unique", 1);

        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("strike", 300);
        set_skill("cuff",300); 
        set_skill("taxue-wuhen",300);
        set_skill("zhentian-quan",300);
        set_skill("kunlun-zhang",300);
        set_skill("xuantian-wuji",300);
        
        map_skill("force","xuantian-wuji");
        map_skill("cuff","zhentian-quan");
        map_skill("strike","kunlun-zhang");
        map_skill("dodge","taxue-wuhen");
        map_skill("parry","zhentian-quan");
        
        prepare_skill("cuff", "zhentian-quan");
        prepare_skill("strike", "kunlun-zhang");
  
        set("combat_exp", 2000000);
        set("max_qi", 30000);
        set("max_jing", 3000);
        set("max_neili", 5000);
        set("eff_jingli",3000);
        set("qi",30000);
        set("jing",3000);
        set("jingli",3000);
        set("neili", 5000);

        setup();  
        if (!random(3))
                add_money("gold", random(5)+1);
        carry_object("/clone/armor/junfu.c")->wear();

}
void init()
{
        object me, ob;  
        int i;    
        ::init();

        ob = this_object();
        if( !query("kill_id", ob) ) return;
                me = find_player(query("kill_id", ob));  
        if( !me ) return;
        if( environment(me) != environment(ob) ) return;
        
        if( interactive(me) && visible(me) &&
            !is_fighting()) {
                NPC_D->copy_from_me(ob, me, 70, 1);
                kill_ob(me);
        }
        remove_call_out("dest");
        call_out("dest", 600, ob);
}

void kill_ob(object me)
{
        object ob = this_object();
        if( !me ) return 0;
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        return ::kill_ob(me);
}

//检查，quest过程不允许死亡
int checking(object me, object ob)
{
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        
        if( !living(me) && living(ob) && query("jing", ob)>0 && query("qi", ob) > 0 ) {
                remove_call_out("checking");
                tell_room(environment(me), HIB"\n"+me->name()+"眼看就是不敌，突然一股劲风袭来，金兵不由手上一松，"+me->name()+"顺势闯出杨家。\n"NOR);
                me->move("/d/jiaxing/njroad3");
                tell_room(environment(me), HIB"\n一个身影突然飞来，待你仔细看来，原来是"+me->name()+"，只见"+me->name()+"突然一顿，竟然昏倒在地。\n"NOR);
                delete(QUESTDIR+"start", me);
                delete_temp(QUESTDIR+"kill", me);
                delete_temp(QUESTDIR+"kill_jinbing", me);
                delete_temp(QUESTDIR+"have_kill", me);
                set("qi",100,me);   
                set("jing",100,me);                                                                                                                                                   //防止玩家意外死亡
                                                                        //dls没有毒的
                set("skybook/shediao/time",time(), me);
                set("skybook/shediao/combat_exp",query("combat_exp",me),me);

                //log_file("quest/SheDiao", sprintf("%s纪录：%s(%s)射雕英雄传之风雪惊变失败。经验%d。\n", ob->name(1),me->name(1),me->query("id"), me->query("combat_exp")) );
                tell_room(environment(ob), ob->name()+"哼了一声：“什么人也敢管本大爷的事！将包惜弱带走！”\n");
                destruct(ob);
                return 1;
        }
        if( !me || me->is_ghost() || query("eff_qi", me)<query("max_qi", me)/15 || query("qi", me)<query("max_qi", me)/20 || environment(me) != environment(ob)){
                remove_call_out("checking");
                remove_call_out("do_lost");
                call_out("do_lost",0);
                return 1;
        }
}
void do_lost()
{
        object me,ob;
        ob = this_object();
        if(!ob) return;
        me=present(query("kill_id",ob),environment(ob));
        if( !me ) me = find_player(query("kill_id", ob));
        if(  me )
        {
                delete(QUESTDIR+"start", me);
                delete_temp(QUESTDIR+"kill", me);
                delete_temp(QUESTDIR+"have_kill", me);
                delete_temp(QUESTDIR+"kill_jinbing", me);
                set("skybook/shediao/time",time(), me);
                set("skybook/shediao/combat_exp",query("combat_exp",me), me);
                //log_file("quest/SheDiao", sprintf("%s纪录：%s(%s)雪山飞狐复仇失败。经验%d。\n", ob->name(1),me->name(1),me->query("id"), me->query("combat_exp")) );
        }
        tell_room(environment(ob), ob->name()+"哼了一声：“这点本事也敢管本大爷的事！”\n");
        destruct(ob);
}

void dest(object ob)
{
        if( !ob ) return;
        tell_room(environment(ob), HIR+"\n"+ob->name()+"哼了一声，点子厉害，我们撤~~~~~~~\n"NOR);
        destruct(ob);
}
varargs void die(object killer)
{
        object me;
        object ob=this_object();
        
        if( !killer ) killer = ob->query_last_damage_from();
        {
                me = killer;
                if( query("id", killer) != query("kill_id", ob) )
                        return 0;
                if(query_temp(QUESTDIR+"start", me)) 
                { 
                        if( !query_temp(QUESTDIR+"kill", me) )
                        {
                                addn_temp(QUESTDIR+"kill_jinbing",1, me);
                                if( query_temp(QUESTDIR+"kill_jinbing", me) == 2 )
                                {
                                        set_temp(QUESTDIR+"kill",1,me);
                                        set_temp(QUESTDIR+"have_kill",1,me);
                                        delete_temp(QUESTDIR+"kill_jinbing",me);
                                }
                        }
                }
        }
        return ::die();
}

