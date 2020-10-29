// doc.c

#include <ansi.h>
inherit F_CLEAN_UP;

int  help(object);
void QueryNpcInfo(string);
void QueryRoomInfo(string);
void QueryItemInfo(string);
string QuerySkill(object);
string QueryAction(object,object);
string QueryEquipProp(object,mapping);

int main(object me,string arg)
{
        string path,var;
        string *filename;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! arg || sscanf(arg,"%s %s", path, var) != 2)
        {
                return help(me);
        }

        if (file_size(path = resolve_path(query("cwd", me), path)) != -2)
                return notify_fail("没有这个目录！\n");

        seteuid(getuid());
        if (path[sizeof(path)-1] != '/')
                path += "/";

        switch(var)
        {
        case "-npc":
        case "-NPC":
                QueryNpcInfo(path);
                break;
        case "-room":
        case "-ROOM":
                QueryRoomInfo(path);
                break;
        case "-item":
        case "-ITEM":
                QueryItemInfo(path);
                break;
        default:
                write("参数不对，请重新输入！\n");
                break;
        }

        return 1;
}

void QueryNpcInfo(string path)
{
        string filename;
        string *file;
        object obj, me = this_player();
        int num = 0;

        filename = path + "文档归类之NPC篇";

        if (file_size(filename) > 0)
                rm(filename);

        file = get_dir(path);
        foreach(string tmp in file)
        {
                if (file_size(tmp) == -2)
                        continue;
                write(sprintf("  整理（%-15s）中...", tmp));
                reset_eval_cost();
                obj = new(path + tmp);
                if (! objectp(obj))
                {
                        write(RED " ...失败！\n" NOR);
                        continue;
                }
                if( !obj->is_character() || !query("name", obj) )
                {
                        write(RED "NOT NPC！\n" NOR);
                        continue;
                }
                num ++;
                write_file(filename, GRN "==================================================\n" NOR, 0);
                write_file(filename, RED "文件序号：" NOR + num + "\n", 0);
                write_file(filename, RED "文件名称：" NOR + tmp + "\n", 0);
                write_file(filename,WHT"中文名字："NOR+query("name", obj)+"\n",0);
                write_file(filename, WHT "英文ＩＤ: " NOR + sprintf("%s", implode(obj->parse_command_id_list(), ",")) + "\n", 0);
                write_file(filename, QuerySkill(obj), 0);
                write_file(filename, "--------------------------------------------------\n");

                write_file(filename, sprintf("【  精  】%10d      【 精力 】%d \n",
                                             query("max_jing", obj),query("max_jingli", obj)));
                write_file(filename, sprintf("【  气  】%10d      【 内力 】%d (+%d)\n",
                                             query("max_qi", obj),query("max_neili", obj),query("jiali", obj)));
                write_file(filename, sprintf("【 食物 】%10d      【 潜能 】%d \n",
                                             query("food", obj),query("potential", obj)));
                // write_file(filename, sprintf("【 饮水 】%10d      【 经验 】%s \n",
                //query("water", obj),query("combat_exp", obj)));


                destruct(obj);
                write(YEL " ...成功。 \n" NOR);
        }

        write_file(filename, "==================================================\n", 0);
        write_file(filename, "    本目录下总共有" GRN + num + NOR "个NPC文件！\n", 0);
        write("=========================================\n");
        write("      共整理（"GRN + chinese_number(num) + NOR"）个NPC文件   \n\n");
        me->start_more(read_file(filename, 1));
}

void QueryRoomInfo(string path)
{
        string filename;
        string *file;
        object obj;
        object finder = new("/clone/npc/trashcan");//任何一个(living object)
        object me = this_player();
        int num = 0;

        filename = path + "文档归类之ROOM篇";

        if (file_size(filename) > 0)
                rm(filename);

        file = get_dir(path);
        foreach(string tmp in file)
        {
                if (file_size(path+tmp) == -2)
                        continue;

                write(sprintf("  整理（%-15s）中...", tmp));
                reset_eval_cost();
                obj = load_object(path + tmp);

                if (! objectp(obj))
                {
                        write(RED" ...失败！\n"NOR);
                        continue;
                }

                if (obj->is_character() || ! stringp(query("short", obj)))
                {
                        write(RED "NOT ROOM\n" NOR);
                        continue;
                }

                num ++;
                write_file(filename, "--------------------------------------------------\n", 0);
                write_file(filename, YEL "房间序号：" WHT + num + "\n" NOR, 0);
                write_file(filename,YEL"房间名称："WHT+query("short", obj)+"("+tmp+")\n"NOR,0);
                write_file(filename,YEL"房间坐标："WHT"（"+query("coor/x", obj)+","+
                           query("coor/y", obj)+","+query("coor/z", obj)+"）\n"NOR,0);
                write_file(filename, QueryAction(obj, finder), 0);
                if( mapp(query("coor", obj)) )
                        write(YEL " ...成功\n" NOR);
                else
                        write(YEL " ...成功" RED "（无坐标）\n" NOR);
        }
        write_file(filename, "==================================================\n", 0);
        write_file(filename, "    本目录下总共有" GRN + num + NOR "个房间！\n", 0);
        write("=========================================\n");
        write("      共整理（" GRN + chinese_number(num) + NOR"）个房间文件   \n\n");
        me->start_more(read_file(filename, 1));
        destruct(finder);
}

void QueryItemInfo(string path)
{
        string filename;
        string *file;
        object obj;
        mapping prop;
        object me = this_player();
        int num = 0;
        int flag = 0;

        filename = path + "文档归类之ITEM篇";

        if (file_size(filename) > 0)
                rm(filename);

        file = get_dir(path);
        foreach(string tmp in file)
        {
                if (file_size(path+tmp) == -2)
                        continue;

                write(sprintf("  整理（%-15s）中...", tmp));
                reset_eval_cost();
                obj = new(path + tmp);

                if (! objectp(obj))
                {
                        write(RED " ...失败！\n" NOR);
                        continue;
                }

                if (obj->is_character() || ! stringp(query("name", obj)))
                {
                        write(RED "NOT ITEM\n" NOR);
                        continue;
                }
                num ++;
                write_file(filename, GRN "--------------------------------------------------\n" NOR, 0);
                write_file(filename, WHT "物品序号：" NOR + num + "\n", 0);
                write_file(filename,WHT"物品名称："NOR+query("name", obj)+"("+
                           implode(obj->parse_command_id_list(), ",") + ")\n", 0);
                write_file(filename,WHT"物品价格："NOR+MONEY_D->price_str(query("value", obj))+"\n",0);
                /*
                if( mapp(prop=query("weapon_prop", obj)) )
                        QueryEquipProp(obj,prop);
                else
                if( mapp(prop=query("armor_prop", obj)) )
                        QueryEquipProp(obj,prop);
                */
                destruct(obj);
                write(YEL " ...成功。 \n" NOR);
        }
        write_file(filename, "==================================================\n", 0);
        write_file(filename, "    本目录下总共有" GRN + num + NOR "个物品！\n", 0);
        write("=========================================\n");
        write("      共整理（" GRN + chinese_number(num) + NOR "）个物品文件   \n\n");
        me->start_more(read_file(filename, 1));
}

string QueryAction(object ob,object finder)
{
        mixed *cmds;
        string msg = "", *str, name;
        int count = 0;

        if( stringp(query("short", ob)) )
                name=query("short", ob);
        else name=query("name", ob);

        finder->move(ob);
        cmds = finder->query_commands();

        if (sizeof(cmds) == 1)
                return("");

        msg += "          " CYN + name + "提供如下指令：\n" NOR;

        foreach(mixed cmd in cmds)
        {
                if (cmd[2] == finder) continue;

                msg += sprintf(WHT "%-10s   " NOR, cmd[0]);
                count++;
                if(count%4 == 0)
                        msg += "\n";
        }
        msg += "\n";
        return msg;
}
string QuerySkill(object ob)
{
        mapping m_skills, m_enable;
        string *sname;
        int i, jibie, lingwu, jilei, xiuwei, opt_all;
        string  msg = "";

        m_skills = ob->query_skills();
        if (! sizeof(m_skills))
                return("");

        msg += "          " + ob->name() + "目前所学过的技能：\n";
        m_enable = ob->query_skill_map();

        if (! mapp(m_enable))
                m_enable = ([]);

        sname = keys(m_skills);
        msg = msg + "--------------------------------------------------\n";

        for (i = 0; i < sizeof( m_skills ); i++)
        {
                msg = msg + sprintf("%s%-12s%-28s%8d\n",
                                    m_enable[ sname[i] ] ? WHT"＊"NOR : "  ",
                                    to_chinese(sname[i]),  " 〖" + sname[i] + "〗",
                                    m_skills[sname[i]]);
        }
        return msg;
}

string QueryEquipProp(object equip,mixed props)
{
        string type, msg = "";
        int *special_props, i;
        int count = 0;
        string *prop;

        if( stringp(type=query("skill_type", equip)) )
                msg += sprintf("兵器类型：%-10s     攻 击 力：%d",
                               type,query("weapon_porp/damage", equip));

        else
        if( stringp(type=query("skill_type", equip)) )
                msg += sprintf("防具类型：%-10s     防 御 力：%d",
                               type,query("armor_porp/armor", equip));

        if (! sizeof(props)) return("");

        msg += "          " + equip->name() + "的其他功效：\n";
        prop = keys(props);
        for (i = 0; i < sizeof(props); i++)
        {
                // foreach(string prop in props){
                if (prop[i] == "armor" || prop[i] == "damage")
                        continue;

                msg += sprintf(WHT "%-12d  " NOR, props[prop[i]]);
                if (i%4 == 0)
                        msg += "\n";
        }
        return msg;
}

int help(object me)
{
        write(@HELP
指令格式：doc 路径名 -种类名
目前提供的种类有：room、npc、item
例：
        doc /d/city/npc -npc
有玩家在线时最好不使用此指令。
HELP);
        return 1;
}
