// chard.c
// From ES2
// Modified by Xiang@XKX

// #pragma optimize
// #pragma save_binary

#define HUMAN_RACE "/adm/daemons/race/human"
#define BEAST_RACE "/adm/daemons/race/beast"
#define MONSTER_RACE "/adm/daemons/race/monster"
#define STOCK_RACE "/adm/daemons/race/stock"
#define BIRD_RACE "/adm/daemons/race/bird"
#define FISH_RACE "/adm/daemons/race/fish"
#define SNAKE_RACE "/adm/daemons/race/snake"
#define INSECT_RACE "/adm/daemons/race/insect"

void create() { seteuid(getuid()); }

void setup_char(object ob)
{
        string race;
        mapping my;

        if( !stringp(race=query("race", ob)) )
        {
                race = "人类";
                set("race", "人类", ob);
        }

        switch(race)
        {
        case "人类":
                HUMAN_RACE->setup_human(ob);
                break;
        case "妖魔":
                MONSTER_RACE->setup_monster(ob);
                break;
        case "野兽":
        case "走兽":
                BEAST_RACE->setup_beast(ob);
                break;
        case "家畜":
        case "走畜":
                STOCK_RACE->setup_stock(ob);
                break;
        case "飞禽":
                BIRD_RACE->setup_bird(ob);
                break;
        case "游鱼":
                FISH_RACE->setup_fish(ob);
                break;
        case "蛇类":
        case "爬蛇":
                SNAKE_RACE->setup_snake(ob);
                break;
        case "昆虫":
                INSECT_RACE->setup_insect(ob);
                break;
        default:
                error("Chard: undefined race " + race + ".\n");
        }

        my = ob->query_entire_dbase();

        if (/*undefinedp*/!(my["jing"]))
                my["jing"] = my["max_jing"];
        if (/*undefinedp*/!(my["qi"]))
                my["qi"] = my["max_qi"];

        if (/*undefinedp*/!(my["eff_jing"]) || my["eff_jing"] > my["max_jing"])
                my["eff_jing"] = my["max_jing"];
        if (/*undefinedp*/!(my["eff_qi"]) || my["eff_qi"] > my["max_qi"])
                my["eff_qi"] = my["max_qi"];

        if (/*undefinedp*/!(my["shen_type"])) my["shen_type"] = 0;

        if (/*undefinedp*/!(my["shen"]))
        {
                if (userp(ob))
                        my["shen"] = 0;
                else
                {
                        my["shen"] = my["shen_type"]*my["combat_exp"]/10;
                }
        }

        if (! ob->query_max_encumbrance())
        {
                if (userp(ob) && MEMBER_D->is_valid_member(ob))
                        ob->set_max_encumbrance(80000 + query("str", ob) * 8000 + ob->query_str() * 1200 + ob->query_jingmai_buff("max_encumbrance"));
                else
                        ob->set_max_encumbrance(40000 + query("str", ob) * 4000 + ob->query_str() * 600 + ob->query_jingmai_buff("max_encumbrance"));
        }

        ob->reset_action();
        ob->update_killer();
}

varargs object make_corpse(object victim, object killer)
{
        int i;
        object corpse, *inv;

        if( victim->is_ghost() || victim->is_undead() || query("no_corpse", victim) )
        {
                inv = all_inventory(victim);
                inv->owner_is_killed(killer);
                inv -= ({ 0 });
                i = sizeof(inv);
                while(i--) inv[i]->move(environment(victim));
                return 0;
        }

        corpse = new(CORPSE_OB);
        corpse->make_corpse(victim, killer);
        return corpse;
}
