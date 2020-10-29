// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m南[1;37m海[1;33m狂[1;32m尼[2;37;0m[2;37;0m", ({"knock"}));        
        set("gender", "男性");                
        set("long", "一条老青龙，拜入南海老尼姑门下，男的拜尼姑，悲哀啊！[2;37;0m
它是邵四丰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "winjoetwo");
        set("owner_name", "邵四丰");
        set_temp("owner", "winjoetwo");
        set_temp("owner_name", "邵四丰");
        ::setup();
}
