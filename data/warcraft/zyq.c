// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m红尘一步终[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "一步了却红尘愿。[2;37;0m
它是剑宗的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zyq");
        set("owner_name", "剑宗");
        set_temp("owner", "zyq");
        set_temp("owner_name", "剑宗");
        ::setup();
}
