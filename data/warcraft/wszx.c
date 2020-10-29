// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("虎丐[2;37;0m[2;37;0m", ({"hugai"}));        
        set("gender", "女性");                
        set("long", "虎丐[2;37;0m
它是墨丐的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "wszx");
        set("owner_name", "墨丐");
        set_temp("owner", "wszx");
        set_temp("owner_name", "墨丐");
        ::setup();
}
