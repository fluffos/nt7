#include <ansi.h>
inherit NPC;
int ask_me();
string* goods = ({
       __DIR__"obj/shoujuan",
       __DIR__"obj/yangpi",
       __DIR__"obj/madao",
       __DIR__"obj/shoujuan",
       __DIR__"obj/shoujuan",
       __DIR__"obj/shoujuan",
       __DIR__"obj/jiunang",
       __DIR__"obj/shoujuan",
});
void destob(object ob);
void create()
{
        set_name("苏普", ({ "supu"}));
        set("gender", "男性");
        set("age", 21);
        set("long", "一个年轻的哈萨克牧羊人, 哈萨克第一勇士苏鲁克的儿子。\n");
        set("attitude", "heroism");
        set("combat_exp", 70000);
        set("shen", 3000);
        set("str", 32);
        set("int", 20);
        set("con", 24);
        set("dex", 20);
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 400);
        set("max_neili", 400);
        set_skill("unarmed", 30);
        set_skill("blade", 40);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set("inquiry", ([
            "阿曼" : "阿曼是我的心上人，我每次杀了野狼都会送她狼皮。\n",
            "李文秀" : "她的歌唱得最好听的了，有人说她比天铃鸟唱得还好。
但这几年来，我一直没听到她唱歌，一直没在见到她。\n",
            "摔跤" : (: ask_me :),
            "比试" : (: ask_me :),
            "计爷爷" : "就是计老人啊，他会酿又香又烈的美酒，会医牛羊马匹的疾病。\n",
            "苏鲁克" : "那是我阿爹，是哈萨克族的第一勇士！哈哈！\n",
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
"苏普自豪地嚷道: 我也要学我阿爹成为哈萨克第一勇士。\n",
"苏普自言自语: 从哪儿去弄一张上等的狼皮，送给阿曼呢? \n",
        }) );
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/yangao")->wear();
        carry_object(__DIR__"obj/jiunang");
}

int ask_me()
{
        if( query_temp("supu_fight", this_player())){
            command("say 我们不是比试过了吗？");
            return 1;
            } 
        if( !query_temp("supu_accept", this_player())){
            command("say 我是草原未来第一勇士，你凭什么和我比试呢？");
            return 1;
            } 
        else {
        message_vision("$N看了$n一眼，用不太标准的汉话说道：
我是未来的草原第一勇士，这位汉族"+RANK_D->query_respect(this_player())+"你就和我切搓(fight)几下吧？\n", this_object(), this_player());
        set_temp("supu1", 1, this_player());
        return 1;
        }
}

int accept_fight(object ob)
{
        object me;
        me = this_object();
        if( query("eff_qi", me)<query("max_qi", me) || 
           query("qi", me)<query("eff_qi", me) || 
           query("neili", me)<query("max_neili", me)){
           message_vision(CYN"$N对$n说：我还没有休息好，你等一会儿吧。\n"NOR, ob, me);
           return 0;
           }
        if( query_temp("supu1", ob)){
        message_vision(CYN"$N对$n说：好吧，那我就同你切搓几招吧，点到为止。\n"NOR, ob, me);
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        delete_temp("supu1", ob);
        delete_temp("supu_accept", ob);
        return 1;
        }
        else return 0;
}

int checking(object me, object ob)
{
        object good;
        int my_max_qi, his_max_qi;
           seteuid(getuid());
        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);
        if (me->is_fighting()){
                call_out("checking",1, me, ob);
                return 1;
                }
        if ( !present(ob, environment()) ) return 1; 
        if( (query("qi", me)*100/my_max_qi) <= 50){
            message_vision(CYN"$N对$n不住地赞叹：你们汉人果然不一般，我服输了，送你一些礼物。\n"NOR, me, ob);
             good = new(goods[random(sizeof(goods))]); 
            set("owner",query("id",  ob), good);
            good->move(ob);
            set_temp("supu_fight", 1, ob);
            message_vision("$N交给$n一件礼物。\n", me, ob);
            message_vision(CYN"$N说道：我要回去陪阿曼了，有缘再相见吧。\n"NOR, me);            
            message_vision("$N带着灰狼皮离开了"+query("short", environment(me))+"。\n",me);
            destruct(this_object());
            return 1;
            }
        if( (query("qi", ob)*100/his_max_qi)<50){
                message_vision(CYN"$N冲着$n一撇嘴，说道：你们汉人的武学不过如此。\n"NOR, me,ob);
                message_vision("$N对$n行了个礼，垂头丧气地离开了这里。\n",ob, me);
//                ob->move("/u/snowman/hj/road");
//                message_vision("$N垂头丧气地走回来。\n", ob);
                return 1;
               }
        return 1;
}

int accept_object(object who, object ob)
{
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return 0;
        if (userp(ob)) {
               command("?"+query("id", who));
               command("say 你这汉人强盗，把人打晕想干什么？");
               this_object()->kill_ob(who);    
               return notify_fail("糟糕，穿邦了！\n");
               }
        if( query("name", ob) == "灰狼皮"){
                command("ah"+query("id", who));
                command("say 你杀死了大灰狼！看来你也是个勇士，要不要和我比试一下？\n");                
                set_temp("supu_accept", 1, who);
        message_vision("$N看了$n一眼，用不太标准的汉话说道：
我是未来的草原第一勇士，这位汉族"+RANK_D->query_respect(this_player())+"你就和我切搓(fight)几下吧？\n", this_object(), this_player());
        set_temp("supu1", 1, this_player());
                call_out("destob",0,ob);                         
            return 1;
        }        
        command("smile"+query("id", who));
        command("say 谢谢你啦。");
        call_out("destob",0,ob);  
        return 0;
}
void destob(object ob)
{
        destruct(ob);
}
