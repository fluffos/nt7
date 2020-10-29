// person used in quest

inherit CLASS_D("generate") + "/chinese";

int  accept_object(object who, object ob);

void random_move();
string do_move();
void die();
int  leave();
int  is_stay_in_room()        { return 1; }

void create()
{
        ::create();
        set("gender",query("gender"));
        set("age", 30 + random(30));
        if (arrayp(query("from")) && sizeof(query("from")))
                set("long",query("from")[random(sizeof(query("form")))] + "\n");
        else
                set("long","");
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set("xxtarget",1);

        set("inquiry", ([
                "战斗"   : (: do_move :),
                "challenge"  : (: do_move :),
        ]) );

        set("scale", 150);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);
        set_temp("born_time", time());
        keep_heart_beat();
}

void set_from_me(object me)
{
        int exp;
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();

        if (my["max_qi"] > 9000)
                my["max_qi"] = 9000;

        if (my["max_jing"] < my["max_qi"] / 2)
                my["max_jing"] = my["max_qi"] / 2;

        if (my["max_jing"] > 6000)
                my["max_jing"] = 6000;

        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];

        exp=query("combat_exp", me)*11/10;
        if (exp > query("combat_exp"))
                set("combat_exp", exp);
}

int accept_fight()
{
        object npc = this_object();
        object me  = this_player();

        mapping myfam;

        myfam=query("family", me);

        if (myfam["family_name"] == "星宿派"){
                command("say 不用比试了，你拿命来吧！");
                if( !npc->is_killing(me) ) npc->kill_ob(me);
        }
        else {
                command("shake");
                command("say 大家都是江湖同道，无故动武岂不是伤了和气？");
                return 0;
        }
        return 1;

}

int accept_hit(object ob)
{
        command("say 你死去吧！");
        command("yun powerup");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        command("say 哼！找死！");
        command("yun powerup");
        return 1;
}

void random_move()
{
        if (time() - query_temp("born_time") > 900)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                destruct(this_object());
                return;
        }
}

string do_move()
{
    object player, room;
    mapping exits;
    string  *dirs;

    player = this_player();
    if( query("player_name") == query("id", player)){
        room = environment(this_object());
        exits=query("exits", room);
        dirs = keys(exits);
        command("go "+dirs[random(sizeof(dirs))]);
        return "出去就出去，有什么不敢？";
    }else {
        return "我今天不是来找你的，你先一边去？";
    }
}

void die()
{
        object ob, corpse, killer;

        if( objectp(killer = query_last_damage_from()) )
        {
                if( !(query("xbiao/dest", killer)) )
                {
                if( query("id", killer) == query("player", this_object())){
                        ob = new("/d/xingxiu/obj/lingpai");
                        ob->move(environment());
message_vision("只听见啪的一声，从$N身上掉下来一件物事。\n", this_object());
                        set("player",query("id",  killer), ob);
                        set("menpai", query("menpai"), ob);
                }
            }
        }
        if( objectp(corpse = CHAR_D->make_corpse(this_object(), killer)) )
                corpse->move(environment());
        remove_all_killer();
        all_inventory(environment())->remove_killer(this_object());
        dismiss_team();
        destruct(this_object());
}