#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void random_move();
void do_swing();
void set_from_me(object me);
void create()
{
        string *names = ({ "青铜猛犸" });

        ::create();
        set_name( names[random(sizeof(names))], ({ "mammoth bronze", "mammoth", "bronze" }));
        set("long", @LONG
这是一个沉睡在皇陵青铜机关兽。身高两丈有余，四肢极为粗壮，长鼻子左右摆动，
嘴部长出一对弯曲的象牙，如同两把弯刀，极为锋利。在东方仙术的作用下，它的行
动虽然迟缓，但力大无穷，长长的象鼻伸缩灵活如意，再加上毛皮刀枪不入，象牙快
如刀刃，端的是极难对付。
LONG);
        set("title", HIR"机关兽" NOR);

        set("str", 150);
        set("con", 150);
        set("dex", 150);
        set("int", 150);
        set("max_qi", 2500000);
        set("max_jing", 1500000);
        set("neili", 2500000);
        set("max_neili", 2500000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        set("auto_perfrom", 1);
        /*
        set("chat_chance", 30);
        set("chat_msg", ({
                (: random_move :)
        }) );
        */
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: do_swing :),
        }) );

        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N散落成一堆青铜。\n\n"NOR);
        set("no_corpse", 1);

        set("rewards", ([
                "exp" : 500,
                "pot" : 120,
                "mar" : 20,
        ]));

        set_temp("apply/attack", 20000);
        set_temp("apply/parry", 20000);
        set_temp("apply/damage", 20000);
        set_temp("apply/unarmed_damage", 20000);
        set_temp("apply/armor", 20000);
        setup();
}

void init()
{
        object me;

        ::init();
        if( !interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0.5, me);
}

void set_from_me(object me)
{
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        set("jiali", query_skill("force") / 2);
}

void do_swing()
{
        object *enemies,enemy;
        string msg;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies)==0 )
                return;

        msg = BLU"$N口一张，口中已有七心海棠的药粉,轻轻一吐，一阵无色无味的薄雾向对方飘去。\n"NOR;
        message_vision(msg,this_object());
        foreach( enemy in enemies ) {
                msg = HIY"$n一时大意，已经中了$N的暗算！\n"NOR;
                message_vision(msg,this_object(), enemy);
                enemy->affect_by("poison",
                                  ([ "level" : 1500,
                                     "id":query("id", this_object()),
                                     "name"  : "七心海棠毒",
                                     "duration" : 200 ]));
                tell_object(enemy, HIG "你中了青铜猛犸的七心海棠毒。\n");
                enemy->receive_damage("qi",10000+random(10000),this_object());
                COMBAT_D->report_status(enemy);
                if( !enemy->is_busy() && !enemy->query_all_buff("daomu") )
                        enemy->start_busy(2);
        }
}

int random_move()
{
        mapping exits;
        string *dirs, direction, to_go_place, my_birth_place;
        object env;
        string userid,mazeobj;
        int x,y;

        if( !mapp(exits=query("exits", environment())))return 0;

        dirs = keys (exits);
        direction = dirs[random(sizeof(dirs))];
        env = environment(this_object());
        to_go_place=query("exits/"+direction, env);
        //my_birth_place = file_name(this_object());

        //ccommand("say "+to_go_place);
        if( sscanf(to_go_place,"/f/mausoleum/%s/%s/%d/%d",userid,mazeobj,x,y)!=4 )
                return 1;
        command("go " + direction);
        addn_temp("random_move", 1);
        return 1;
}
