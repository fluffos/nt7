// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m火焰脚[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "不看不看[2;37;0m
它是山治的魔幻兽。
");
        set("race_type", "玄武");
        set("magic/type", "water");
        set("owner", "xlqxd");
        set("owner_name", "山治");
        set_temp("owner", "xlqxd");
        set_temp("owner_name", "山治");
        ::setup();
}
