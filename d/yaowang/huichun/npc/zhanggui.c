#include <ansi.h>
inherit NPC;

int ask_me();
int ask_ok();

void create()
{
        set_name("姜小铁", ({ "jiang xiaotie", "jiang", "xiaotie" }) );
        set("title", HIB"药王谷"NOR+WHT"管事"NOR);
        set("long", "他是回春堂的管事，负责回春堂的杂役。\n" );
        set("gender", "男性" );
        set("age", 17);
        set("combat_exp", 10000);
        set("attitude", "friendly");

        set("inquiry", ([
                "job" : (: ask_me :),
                "ok" : (: ask_ok :),
        ]));

        setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{
        int i=(query("eff_qi", ob)*100)/query("max_qi", ob);

        if( query("party/party_name", ob) == "药王谷"){
                command("say 这位兄弟辛苦了，快请进！\n");
                return 1;}

        if (i<=30) {
                command("wa "+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你受了重伤啊！快请到里面让药王谷医师给你看看吧！\n");
                return 1;}

        if (i<=60) {
                command("look "+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你伤得不轻啊！快请到里面疗伤吧！\n");
                return 1;}

        if (i<=90) {
                command("pat "+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"，你受了点伤！到里面买包药服下就没事了！\n");
                return 1;}

        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        break;
                }
        }
}

int ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "药王谷"){
                command("say 你不是这里的伙计，这种活怎么能让你干呢？\n");
                return 1; }
        if( query_temp("work_pass", me)){
                command("say 不是让去见谷主了吗？\n");
                return 1; }

        if( (int)me->query_skill("medical",1)>=40 ) {
                command("say 你不需要干这种活的！\n");
                return 1; }

        if( !query_temp("renwu_name", me)){
                ob = new(__DIR__"obj/saoba");
                ob->move(me);
                message_vision(YEL"迟未给了$N一支扫把。\n"NOR, me);
        switch ( random(7) ) {
        case 0 :
                set_temp("renwu_name", "休息室", me);
                command("say 你去打扫(dasao)一下休息室吧！\n");
                return 1;
        case 1 :
                set_temp("renwu_name", "北厅", me);
                command("say 你去打扫(dasao)一下北厅吧！\n");
                return 1;
        case 2 :
                set_temp("renwu_name", "正厅", me);
                command("say 你去打扫(dasao)一下正厅吧！\n");
                return 1;
        case 3 :
                set_temp("renwu_name", "庭院", me);
                command("say 你去打扫(dasao)一下庭院吧！\n");
                return 1;
        case 4 :
                set_temp("renwu_name", "回春堂", me);
                command("say 你去打扫(dasao)一下大门吧！\n");
                return 1;
        case 5 :
                set_temp("renwu_name", "内屋", me);
                command("say 你去打扫(dasao)一下内屋吧！\n");
                return 1;
        case 6 :
                set_temp("renwu_name", "南厅", me);
                command("say 你去打扫一下南厅吧！\n");
                return 1;
                }
        }
        else {
                command("say 你先把活干完吧！\n");
                return 1;
        }
}

int ask_ok()
{
        object money, me;
        int amount, i,exp,pot;
        object ob;
        
          exp = 25+random(5);
          pot = 5+random(5);
        me = this_player();
        amount = random(3);
        i = random(20);
        if( query_temp("renwu_wancheng", me) >= 100){
                delete_temp("renwu_wancheng", me);
                delete_temp("renwu_name", me);
                if ( ob =present("saoba", me) && !userp(ob) ) {
                        message_vision ("$N放下手中的扫把。\n", me);
                        destruct(ob);
                        money = new ("/clone/money/silver");
                        money->move(me);
                        money->add_amount(amount);
                          addn("combat_exp", exp, me);
                          addn("potential", pot, me);
                          command("say 好！干得不错，这是赏你的！\n");
                                tell_object(me, HIC "你获得了" + chinese_number(exp) + "点" 
                                 "经验和" + chinese_number(pot) + "点潜能。"
                                 "\n" NOR);
                        if(i=1) {addn("max_jingli",1,me);} 
                } else { 
                        command("hmm "+query("id", me));
                        command("say 真没用，让你干活，你把工具都丢了！\n");
                        }
        } else {
                command("say 你赶快去把活干完啊！\n");
                }
        return 1;
}
