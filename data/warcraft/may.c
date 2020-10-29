// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m五小月份[2;37;0m[2;37;0m", ({"mayaa"}));        
        set("gender", "男性");                
        set("long", "阿[2;37;0m
它是五月份的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "may");
        set("owner_name", "五月份");
        set_temp("owner", "may");
        set_temp("owner_name", "五月份");
        ::setup();
}
