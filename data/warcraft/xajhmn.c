// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m旺财[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "这是一只麒麟幼兽？或者就是一条土狗？就当是土狗吧，狗名旺财！[2;37;0m
它是鸿钧的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xajhmn");
        set("owner_name", "鸿钧");
        set_temp("owner", "xajhmn");
        set_temp("owner_name", "鸿钧");
        ::setup();
}
