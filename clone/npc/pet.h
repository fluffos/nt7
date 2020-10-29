// pet.c 宠物

#include <ansi.h>
#include <command.h>

#define RIDE_CMD              "/cmds/std/ride"
#define UNRIDE_CMD            "/cmds/std/unride"

inherit NPC;
inherit F_NOCLONE;
inherit F_OBSAVE;
inherit F_UNIQUE;

int is_pet() { return 1; }

int is_stay_in_room() { return 1; }

void create()
{
        set_name("宠物", ({ "pet" }) );
        set("race", "野兽");
        set("gender", "雄性");
        set("age", 2 + random(3));
        set("long", "玩家可以骑上它去指定的地方(rideto)。\n");        
        set("ridable", 1);
        set("no_sell", 1);
        set("no_put", 1);
        
        set("int", 30);
        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("shen_type", 0);
        set("combat_exp",50000);
        set("attitude", "peaceful");        
        set("limbs", ({ "头部", "腹部", "尾巴","后腿","前腿" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set_temp("apply/attack", 100);
        set_temp("apply/damage", 100);
        set_temp("apply/defence",100);
        set_temp("apply/armor", 100);
        
        set_temp("owner_id", "lonely");
        
        if (! check_clone()) return 0;

        setup();
        ::restore();
}

int receive_whistle(object me)
{
        object env;
        object temp;

        if ((env = environment()) && env == me)
        {
                write(name() + "你不是正骑着吗？你召唤个什么劲？\n");
                return 1;
        }

        if (env == environment(me))
        {
        } else
        {
                if (env)
                {
                        if (env->is_character() && environment(env))
                                        env = environment(env);

                        message("vision", HIG "突然" + name() + HIG "狂奔"
                                HIG "而去，瞬间消失了！\n\n" NOR, env);

                        if (interactive(env = environment()))
                        {
                                delete_temp("is_riding", env);
                                this_object()->delele_temp("is_rided_by");
                                tell_object(env, HIM + name() +
                                                 HIM "忽然离你而去了！\n" NOR);
                        }
                }

                message_vision(HIG "$n" HIG "不知从哪里窜到$N" HIG "面前！\n\n" NOR,
                               me, this_object());
        }

        move(environment(me));

        if (environment() != environment(me))
                return 1;
                
        if (objectp(temp = query_temp("is_riding")))
                UNRIDE_CMD->main(me);
                                
        RIDE_CMD->main(me, query("id"));
        return 1;
}

// 接受存盘数据的接口函数
int receive_dbase_data(mixed data)
{
        if (! mapp(data))
                return 0;

        if (stringp(data["user"]))
                set_temp("owner_id", data["user"]);

        return 1;
}

// 进行保存数据的接口函数
mixed save_dbase_data()
{
        mapping data;
        object  user;

        data = ([ ]);

        if (! objectp(user = environment()))
                data += ([ "user" : query_temp("owner_id") ]);
        else
        if (playerp(user))
                data+=(["user":query("id", user)]);

        return data;
}

void die()
{
        destruct(this_object());
        return;
}
