// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m白虎[2;37;0m[2;37;0m", ({"realwtiger"}));        
        set("gender", "女性");                
        set("long", "一只真正的白虎。[2;37;0m
它是阿拉丁的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "alar");
        set("owner_name", "阿拉丁");
        set_temp("owner", "alar");
        set_temp("owner_name", "阿拉丁");
        ::setup();
}
