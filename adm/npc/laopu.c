// laopu.c 扫地老仆

#include "/d/room/roomnpc/roomnpc.h"

inherit NPC;
inherit F_GUARDER;

void do_wield();
void do_unwield();
int  accept_object(object who, object ob);
string query_save_file()
{
        object env;

        if (!objectp(env = environment()) ||
            strsrch(base_name(env),"/data/room/") == -1 ||
            !query("room_owner_id", env) )
                return 0;

        return sprintf("/data/room/%s/laopu",query("room_owner_id", env));
}
int restore()
{
        string file;
        if( stringp(file = this_object()->query_save_file()) && file_size(file + __SAVE_EXTENSION__) > 0 )
                return restore_object(file);
        return 0;
}

void init_status()
{
        int lvl;

        restore();
        set("jiali", this_object()->query_skill("force")/2);
        lvl = this_object()->query_skill("force",1) - 1;
        lvl = lvl*lvl*lvl/10;
        if (lvl < 10000000) lvl = 10000000;
        set("combat_exp",lvl);
        set("auto_perform", 1);
        
        if (stringp(query_save_file()) && environment())
                set("owner",query("room_owner", environment()));
        reset_action();
        full_self();
}

void setup()
{
        ::setup();
        call_out("init_status",1); 
}

int save()
{
        string file;
        
        if (!query("startroom") ||
            !environment() ||
            query("startroom") != base_name(environment()))
                return 0;

        if( stringp(file = this_object()->query_save_file()) ) {
                assure_file(file + __SAVE_EXTENSION__);
                return save_object(file);
        }
        return 0;
}

void create()
{
        set_name("扫地老仆", ({"lao pu", "saodi laopu"}) );
        set("gender", "男性" );
        set("age", 50 + random(20));
        set("long", "这是一个扫地的老仆人，不过看上去似乎身怀绝技。\n");
        set("attitude", "friendly");

        set("max_qi", 4000);
        set("max_jing", 8000);
        set("max_neili", 4000);
        set("neili", 4000);
        set("combat_exp",10000000);
        set("no_get",1);
        set("max_vip",10);
        set("auto_perform",1);

        set_skill("force", 800);
        set_skill("parry", 800);
        set_skill("dodge", 800);
        set_skill("strike",800);
        set_skill("claw",800);
        set_skill("jiuyang-shengong", 800);
        set_skill("lingbo-weibu", 800);
        set_skill("qiankun-danuoyi", 800);
        set_skill("jiuyin-baiguzhao", 800);
        set_skill("cuixin-zhang", 800);

        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("strike" , "cuixin-zhang");

        prepare_skill("claw", "jiuyin-baiguzhao");
        prepare_skill("strike", "cuixin-zhang");

        /*
        set("chat_chance", 30);
        set("chat_msg", ({
                (: do_unwield :),
        }));
        */

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: do_wield :),
        }));

        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        ::init();
        add_action("do_invite", "invite");
        add_action("do_show", "show");
        add_action("do_vip", "vip");
        add_action("list_vip", "listvip");
        add_action("add_force", "addforce");
        add_action("add_skill", "addskill");
        add_action("buy_vip", "buyvip");
        add_action("add_hujiu", "addhujiu");
}

void do_unwield()
{
        command("yun powerup");
        command("yun shield");
}

void do_wield()
{
        command("yun powerup");
        command("yun shield");
}

int accept_object(object who, object ob)
{
//      object obn;

        if( !query("money_id", ob) )
                return 0;

        if (is_owner(who))
        {
                message_vision(name() + "对$N施了一礼。\n", who);
                destruct(ob);
                return 1;
        }
        return 0;
}

int accept_hit(object ob)
{
        if (is_owner(ob))
        {
                message_vision("$N愁眉苦脸的对$n道：“可不要和我开这"
                               "种玩笑！”\n", this_object(), ob);
                return 0;
        }

        command("yun powerup");
        command("yun shield");

        if (query("can_hujiu") && query("owner"))
                CHANNEL_D->do_channel( this_object(), "chat", query("owner") + "快来啊，有人攻打到大门口来啦！");

        return ::accept_hit(ob);
}

int accept_fight(object ob)
{
        if (is_owner(ob))
        {
                message_vision("$N吓了一跳，慌忙对$n道：“小的不敢，小"
                               "的不敢！”\n", this_object(), ob);
                return 0;
        }

        command("yun powerup");
        command("yun shield");

        if (query("can_hujiu") && query("owner"))
                CHANNEL_D->do_channel( this_object(), "chat", query("owner") + "快来啊，有人攻打到大门口来啦！");

        return ::accept_fight(ob);
}

int accept_kill(object ob)
{
        if (is_owner(ob))
        {
                message_vision("$N一声长叹，道：“既然主人不留我了，罢"
                               "罢罢！合则留，不合则去！我走了。”\n"
                               "说罢，老人丢下扫把，飘然而去。\n",
                               this_object(), ob);
                destruct(this_object());
                return 0;
        }

        command("yun powerup");
        command("yun shield");

        if (query("can_hujiu") && query("owner"))
                CHANNEL_D->do_channel( this_object(), "chat", query("owner") + "快来啊，有人攻打到大门口来啦！");

        return ::accept_kill(ob);
}
