// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m毛头[2;37;0m[2;37;0m", ({"zhg"}));        
        set("gender", "女性");                
        set("long", "长的很丑[2;37;0m
它是买菜大婶的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "kamuls");
        set("owner_name", "买菜大婶");
        set_temp("owner", "kamuls");
        set_temp("owner_name", "买菜大婶");
        ::setup();
}
