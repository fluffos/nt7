// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m玄冥[1;32m鬼凤[2;37;0m[2;37;0m", ({"xmgf"}));        
        set("gender", "男性");                
        set("long", "一头来自地狱的鬼凤。[2;37;0m
它是玄冥子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xmz");
        set("owner_name", "玄冥子");
        set_temp("owner", "xmz");
        set_temp("owner_name", "玄冥子");
        ::setup();
}
