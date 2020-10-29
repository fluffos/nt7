// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("快意[2;37;0m[2;37;0m", ({"fft"}));        
        set("gender", "女性");                
        set("long", "一只朱雀[2;37;0m
它是史丹佛的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "stenford");
        set("owner_name", "史丹佛");
        set_temp("owner", "stenford");
        set_temp("owner_name", "史丹佛");
        ::setup();
}
