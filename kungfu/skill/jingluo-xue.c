inherit SKILL;

string type() { return "knowledge"; }
void skill_improved(object me)
{       
        if (me->query_skillo("jingluo-xue", 1) >= 100)
        {
                MYGIFT_D->check_mygift(me, "newbie_mygift/jingluoxue");
        }
}

