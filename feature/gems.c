#include <ansi.h>
#include <dbase.h>
#include <name.h>

#include "gems.h"

int valid_gem(string gem, int level)
{
        if (gem != "ruby" && gem != "topaz" && gem != "sapphire"
&& gem != "emerald" && gem != "amethyst" && gem != "diamond" && gem != "skull")
                return 0;
        if (level < 1 || level > 8)
                return 0;

        return 1;
}

string query_gem_name(string socket, int level)
{
        return sprintf("%s%s%s"NOR, gems_color[socket], gems_level[level - 1], gems[socket]);
}

string query_gem_id(string socket, int level)
{
        return sprintf("%s %s", gems_level_id[level - 1], socket);
}

string query_all_effect(string socket)
{
        string msg = gems_color[socket] + "这是一颗宝石，上面似乎附着某种神奇的魔力：\n"NOR;
        msg += sprintf("\t兵器 - %s\n", weapon_effect[socket]);
        msg += sprintf("\t防具 - %s\n", armor_effect[socket]);
        msg += sprintf("\t戒指 - %s\n", ring_effect[socket]);
        return msg;
}

void set_weapon_desc()
{
        int i, level, sockets = query("sockets/max");
        string socket, desc = query("long");
//add by hxsd
        if (sockets >5)
{
        set("sockets/max",5);
        sockets=5;
}
//

        if (sockets < 1) return;

        if (!stringp(desc)) desc = "";
        desc += sprintf("上面似乎可以镶嵌着%d颗魔法石！\n", sockets);
        for (i = 1; i <= sockets; i++) {
                socket = query(sprintf("sockets/socket%d", i));
                level = query(sprintf("sockets/socket%d_level", i));
                if (valid_gem(socket, level))
                        desc += sprintf("\t[%s] - %s\n", query_gem_name(socket, level), weapon_effect[socket]);
        }
        set("long", desc);
        return;
}

void set_armor_desc()
{
        int i, level, sockets = query("sockets/max");
        string socket, desc = query("long");
//add by hxsd
        if (sockets >5)
{
        set("sockets/max",5);
        sockets=5;
}
//
        if (sockets < 1) return;
        if (!stringp(desc)) desc = "";
        desc += sprintf("上面似乎可以镶嵌着%d颗魔法石！\n", sockets);
        for (i = 1; i <= sockets; i++) {
                socket = query(sprintf("sockets/socket%d", i));
                level = query(sprintf("sockets/socket%d_level", i));
                if (valid_gem(socket, level))
                        desc += sprintf("\t[%s] - %s\n", query_gem_name(socket, level), armor_effect[socket]);
        }
        set("long", desc);
        return;
}

void set_ring_desc()
{
        int i, level, sockets = query("sockets/max");
        string socket, desc = query("long");
//add by hxsd

        if (sockets >3)
{
        set("sockets/max",3);
        sockets=3;
}

        if (sockets < 1) return;

        if (!stringp(desc)) desc = "";
        desc += sprintf("上面似乎可以镶嵌着%d颗魔法石！\n", sockets);
        for (i = 1; i <= sockets; i++) {
                socket = query(sprintf("sockets/socket%d", i));
                level = query(sprintf("sockets/socket%d_level", i));
                if (valid_gem(socket, level))
                        desc += sprintf("\t[%s] - %s\n", query_gem_name(socket, level), ring_effect[socket]);
        }
        set("long", desc);
        return;
}

object new_gem(string gem, int lev)
{
        object ob;

        ob = new("/clone/gem/gem.c");
        if (!ob) return ob;

        if (!gem || gem == "")
                gem = ob->query("material");
        if (!lev || lev == 0)
                lev = ob->query("level");
        if (!valid_gem(gem, lev)) return ob;

        ob->set_name(query_gem_name(gem, lev), ({query_gem_id(gem, lev)}));
        ob->set("long", query_all_effect(gem));
        ob->set("value", 100000 * lev * lev * lev);
        ob->set("material", gem);
        ob->set("level", lev);
        return ob;
}
