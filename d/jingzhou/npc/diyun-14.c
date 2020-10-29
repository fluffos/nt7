// This program is a part of NT MudLIB

#include <ansi.h>;
inherit NPC;

#define QUESTDIR  "skybook/连城诀/"
#define QUESTDIR1 "skybook/连城诀/复仇篇/"
#define QUESTDIR2 "skybook/连城诀/解救丁典篇/"
#define QUESTDIR3 "skybook/连城诀/雪谷激斗篇/"
#define QUESTDIR4 "skybook/连城诀/宝藏篇/"
#define QUESTDIR5 "skybook/连城诀/武功/"

string ask_me();
string ask_me2();
string ask_book();
string ask_book2();
void do_kill(object ob);

void create ()
{
        object weapon;
        set_name("狄云", ({"di yun","di"}));
        set("long", "他长脸黝黑，颧骨微高，粗手大脚，象是湘西乡下常见的庄稼汉子。\n");
        set("gender", "男性");
        set("age", 24);
        set("combat_exp", 20000000);
        set("max_qi",20000);
        set("max_jing",20000);
        set("max_neili",30000);
        set("qi",20000);
        set("jing",20000);
        set("neili",30000);
        set("str", 125);
        set("int", 125);
        set("con", 125);
        set("dex", 125);
        set("per", 26);

        set_skill("force", 320);
        set_skill("dodge", 320);
        set_skill("sword", 220);
        set_skill("parry", 320);
        set_skill("yanfly", 200);
        set_skill("liancheng-jianfa", 320);
        set_skill("shenzhaojing", 300);
        set_skill("xuedao-daofa", 200);
        
        map_skill("sword", "liancheng-jianfa");
        map_skill("force", "shenzhaojing");
        map_skill("blade", "xuedao-daofa");
        map_skill("parry", "xuedao-daofa");
        map_skill("unarmed", "shenzhaojing");
        map_skill("dodge", "yanfly");

        set("chat_chance_combat", 90);
        set("chat_msg_combat", ({
                (: perform_action, "sword.cijian" :),
                (: perform_action, "sword.erguang" :),
                (: perform_action, "sword.qujian" :),
                (: perform_action, "blade.huan" :),
                (: perform_action, "blade.ying" :),
                (: perform_action, "blade.shi" :),
                (: perform_action, "blade.xue" :),
        
        }) );
                
        set("inquiry", ([
                "水笙" : (: ask_me :),
                "剑谱":     (: ask_book :),
                "丁典":     (: ask_book2 :),
                "神照经":     (: ask_book2 :),
                "万震山":     "万震山这个狗贼我非杀了他不可。\n",
        ]));
        
        set_temp("apply/attack", 120);
        set_temp("apply/defense", 120);
        set_temp("apply/armor", 120);
        set_temp("apply/damage", 520);


        set("wucan_count", 1);
        set("baodao_count",1);
        set("book_count",1);
        
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        if (clonep())
        {
                weapon = new( WEAPON_DIR"treasure/xblade" );        
                if ( weapon->violate_unique() )
                {
                        destruct( weapon );
                        weapon = new( "/clone/weapon/gangdao" );
                }
                weapon->move(this_object());
                weapon->wield();
        }
} 

string ask_me()
{
        mapping fam; 
        object ob;
        
        if (query("wucan_count") < 1)
                return "水笙姑娘？她在雪域等着我？";

        addn("wucan_count", -1);
        set_temp("marks/wucan", 1, this_player());
        return "水笙姑娘？她在雪域等着我？她有什么东西捎给我么？";
}

int accept_object(object who, object ob)
{
        object obj;
        int i;
        
        if( (string)query("id", ob) == "wan zhenshan" ) 
        {
                write(HIC "\n狄云说道：这位" + RANK_D->query_respect(who)+"，如此大恩大德，在下实不知何以为报。\n");
                write(HIC "\n狄云大喜道：狗贼！想不到你也有今天！！。\n"NOR);
                call_out("destroying", 1, this_object(), ob);
                set_temp("marks/lianchenpu", 1, who);
                return 1;
        }
        
        if( query("id", ob) != "dachang" )
                return notify_fail("给我这东西有什么用？");
                
        message_vision("狄云笑着说道：“谢谢你！这位" + RANK_D->query_respect(ob) +"，辛苦你了。”\n", who);
        if( !query_temp("marks/wucan", who) )
        {
                return 1;
        }
        obj = new(ARMOR_DIR"treasure/wucanyi");
        delete_temp("marks/wucan", this_player());
        if ( obj->violate_unique() || uptime() < 300)
        {
                destruct( obj );
                return 1;
        }
        message_vision("狄云对$N说道：“这件乌蚕衣也不算是什么宝贝，聊表心意吧！”狄云从怀里掏出一团不起眼的东西，递到$N的手上。\n", who);
        obj->move(this_player());
        return 1;
}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

void do_kill(object ob)
{
        object me, room1;       
        me = this_object();

        if (interactive(ob))
        {
                command("say 你这恶贼竟敢打我剑谱的主意，给我纳命来！\n");
                me->set_leader(ob);
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
 
}       

string ask_book()
{
        object ob, me;
        
        me = this_player();
        if( !query_temp("marks/lianchenpu",me) ) return "你说什么? \n";
        
        if( (int)query("shen", me)<100000 )
                return "剑谱落入宵小之手，难免是万震山第二。\n";

        if( query("book_count") > 0 )
        {               
                write(HIC "狄云说着转身从万震山尸身上搜出一本破旧书本，递了给你。\n");

                add("book_count", -1);
                ob = new ("/clone/book/lian_book");
                ob->move(this_player());
                command("rumor "+query("name",me)+"拿到连城剑谱啦。\n");
                return "这本连城剑谱被这狗贼霸占多时了，现在就赠与你吧。\n";
        }
        else return "你来晚了，现在连城剑谱已不在此处。\n";

}

string ask_book2()
{
        object ob, me;
        int i;
        object fang;
        me = this_player();
        
        if( !query(QUESTDIR+"active", me) )
                return "你说什么? \n";
        
        if( !query_temp("marks/lianchenpu", me) ) 
                return "请先帮我把万震山这恶人抓来吧！ \n";
                
        if( !query_temp("tssword", me) ) 
                return "你帮我找到唐诗剑谱了吗? \n";
        
        if( ((int)query("combat_exp", me)<=1000000) )
        {
                message_vision("$N对$n说道： 你的武功太差了，等武功好点再来吧！\n",this_object(),me);
                return " 快去吧。\n";   
        }
        
        if( ((int)query(QUESTDIR2+"/解救丁典", me)>=1 ))
        {
                message_vision("$N对$n说道： 我不是已经让你去救丁大哥过了吗? \n",this_object(),me);
                return " 快去吧。\n";   
        }
        
        if( (int)query("shen", me)<100000 )
                return "你这恶人，有什么资格去救丁大哥?\n";

        command("bow " + query("id", me));
        message_vision("$N对$n说道： 多谢帮我手刃仇人。\n",this_object(),me);
        message_vision("$N对$n说道： 我大哥丁典被关在江凌知府中，请帮我去看看他吧。\n",this_object(),me);

        set(QUESTDIR2+"/解救丁典", 1, me);
        SKYBOOK_D->check_skybook(me, "连城诀");
        
        i = 200+random(800);
        
        me->add("combat_exp",i+9880);
        me->add("potential",i*12);

        tell_object (me,"你赢得了"+chinese_number(i+9880)+"点经验"+
                   chinese_number(i*12)+"点潜能！\n");

}


