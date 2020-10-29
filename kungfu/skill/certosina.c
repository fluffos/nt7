// certosina.c

inherit SKILL;

string type() { return "technic"; }

int valid_learn(object me)
{
    return 1;
}

void skill_improved(object me)
{       
        if (me->query_skillo("certosina", 1) >= 100)
        {
                MYGIFT_D->check_mygift(this_player(), "newbie_mygift/certosina");
        }
}

