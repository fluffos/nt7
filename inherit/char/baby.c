#define BABY_DIR  "/data/baby/"
#include <ansi.h>
inherit NPC;
inherit F_SAVE;
nosave int last_age_set;

int query_current_neili_limit();
int query_neili_limit();
int query_current_jingli_limit();
int query_jingli_limit();
mixed query_potential_limit();
int query_experience_limit();

void update_age()
{
        if (! environment()) return;

        if (environment()->is_chat_room())
                last_age_set = time();

        if (! last_age_set ) last_age_set = time();
        addn("mud_age", time() - last_age_set);
        last_age_set = time();
        set("age", ((int)query("mud_age") / 518400));
}

string query_save_file()
{
             if (! stringp(query("parents/mother"))) return 0;

             return sprintf(BABY_DIR"%s", query("parents/mother"));
}

int save()
{
            int res;
            update_age();
            res = ::save();
            return res;
}

#define MAX_NEILI_IMPROVE       query("con")
#define MAX_JINGLI_IMPROVE      query("con")

int query_neili_limit()
{
        string *skill_names;
        mapping skills;
        int neili_limit;
        int base_lvl, lvl;
        int tmp;
        int i;
        string fam;

        skills = this_object()->query_skills();
        if (! mapp(skills))
                return 0;

        skill_names = keys(skills);

        base_lvl = ((int) skills["force"]) / 2;
        neili_limit = base_lvl * 10;
        for (i = 0; i < sizeof(skill_names); i++)
        {
                if (file_size(SKILL_D(skill_names[i]) + ".c") == -1)
                {
                        // No such skill
                        continue;
                }

                if (! SKILL_D(skill_names[i])->valid_enable("force"))
                        continue;

                lvl = (int) skills[skill_names[i]];
                tmp = (base_lvl + lvl) * 10;
                tmp += (int) SKILL_D(skill_names[i])->query_neili_improve(this_object());
                if (tmp > neili_limit) neili_limit = tmp;
        }

        neili_limit += neili_limit / 100 * query("improve/neili");
        if (query("breakup"))
                neili_limit += neili_limit / 10 * 3;

        if (query("special_skill/mystery"))
                neili_limit += query("con") * 15;

        fam = query("family/family_name");
        if (query("class") == "bonze" &&
            (fam == "雪山寺" || fam == "少林派" || fam == "峨嵋派" || fam == "血刀门"))
                neili_limit += 500;

        neili_limit += this_object()->query_all_buff("max_neili"); 
        neili_limit += query("drug_addneili");
        neili_limit += query("combat_exp") / 10000;
        return neili_limit;
}

int query_current_neili_limit()
{
        int neili;
        string force;
        string fam;

        force = query_skill_mapped("force");
        neili = (int)query_skill("force", 1) / 2 * 10;
        if (stringp(force) && force != "")
        {
                neili += (int)query_skill(force, 1) * 10;
                neili += SKILL_D(force)->query_neili_improve(this_object());
        }

        neili += neili / 100 * query("improve/neili");
        if (query("breakup"))
                neili += neili / 10 * 3;

        if (query("special_skill/mystery"))
                neili += query("con") * 15;

        fam = query("family/family_name");
        if (query("class") == "bonze" &&
            (fam == "雪山寺" || fam == "少林派" || fam == "峨嵋派" || fam == "血刀门"))
                neili += 500;

        neili += this_object()->query_all_buff("max_neili"); 
        neili += query("drug_addneili");
        neili += query("combat_exp") / 10000;
        return neili;
}

int query_jingli_limit()
{
        int limit;

        limit = ((int)query("magic_points") / 30) + query("int") * 30;
        limit += limit / 100 * query("improve/jingli");
        if (query("animaout"))
                limit += limit / 10 * 4;

        limit += this_object()->query_all_buff("max_jingli"); 
        limit += query("drug_addjingli");
        limit += query("combat_exp") / 20000;
        return limit;
}

int query_current_jingli_limit()
{
        return query_jingli_limit();
}

mixed query_potential_limit()
{
        int p;

        p = (int)query("combat_exp") / 5;
        p += (query_int() / 100) * p;
        if (ultrap(this_object()))
                p += 1000000;
        p += 5000;

        return (int)query("learned_points") + p;
}

int query_experience_limit()
{
        int p;

        if (ultrap(this_object()))
                p = 10000;
        else
        {
                p = query("score");
                if (p < 100)
                        p = p / 2;
                else
                if (p < 300)
                        p = p / 4 + 25;
                else
                if (p < 1100)
                        p = (p - 300) / 8 + 100;
                else
                        p = (p - 1100) / 16 + 200;
                if (p > 8000)
                        p = 8000;
        }

        return (int)query("learned_experience") + p;
}

mixed improve_potential(int n)
{
        int max;

        max = query_potential_limit() - query("potential");
        if (max <= 0) return 0;
        if (max > n) max = n;

        addn("potential", max);
        return max;
}

int improve_experience(int n)
{
        int max;

        max = query_experience_limit() - query("experience");
        if (max <= 0) return 0;
        if (n > max) n = max;
        addn("experience", n);
        return n;
}

int can_improve_neili()
{
        return query("improve/neili") < MAX_NEILI_IMPROVE;
}

int can_improve_jingli()
{
        return query("improve/jingli") < MAX_NEILI_IMPROVE;
}

int improve_neili(int n)
{
        int delta;

        if ((delta = query_neili_limit() - query("max_neili")) <= 0)
                return 0;

        if (n > delta) n = delta;
        addn("max_neili", n);
        return n;
}

int improve_jingli(int n)
{
        int delta;

        if ((delta = query_jingli_limit() - query("max_jingli")) <= 0)
                return 0;

        if (n > delta) n = delta;
        addn("max_jingli", n);
        return n;
}

void die()
{
        object killer, corpse;

        killer = this_object()->query_last_damage_from();

        if (objectp(killer))
        {
                CHANNEL_D->do_channel(find_object(COMBAT_D), "rumor", 
                        "我看见" + this_object()->name() + "被" + killer->name() +
                        "杀害了，真是惨无人道啊！\n" NOR);

                  if (playerp(killer))
                          killer->apply_condition("killer", 1000 + killer->query_condition("killer"));
        } else
                CHANNEL_D->do_channel(find_object(COMBAT_D), "rumor", 
                        "听说" + this_object()->name() +
                        "死了，死状惨不忍睹！\n" NOR);

        if (objectp(corpse = CHAR_D->make_corpse(this_object(), killer)))
                corpse->move(environment());
        addn("combat/dietimes", 1);
        if (objectp(killer) && userp(killer)) addn("combat/PKD", 1);
        addn("shen", - (int)query("shen") / 10);
        addn("combat_exp", -query("combat_exp")/50);

        if (query("potential") > query("learned_points"))
                addn("potential", query("learned_points")-query("potential")/5);
        this_object()->skill_death_penalty();
        save();

        return :: die();
}

void relay_message(string msgclass, string msg)
{
        string fid, mid;
        object fob, mob;
        object me = this_object();
        object env = environment(me);
        
        fid = query("parents/father", me);
        mid = query("parents/mother", me);
        
        fob = find_player(fid);
        mob = find_player(mid);
        
        msg = "\n"+NOR+HIM+"--==--\n"+HIM+">>|"+this_object()->query_idname()+"|<<\n"+NOR+msg+NOR+MAG+"--==--\n\n"NOR;
        
        if( objectp(fob) && query("env/snoop_baby", fob) && env != environment(fob) )
                fob->receive_message(msgclass, msg);
        
        if( objectp(mob) && query("env/snoop_baby", mob) && env != environment(mob) )
                mob->receive_message(msgclass, msg);
                
        return;
}

