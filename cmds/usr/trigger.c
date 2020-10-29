// trigger.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define MAX_TRIGGER_CMDS  10
#define TRIGGER_CMD_SIZE  21

protected void done_input(object me, string text);
protected void user_quit(object me);
int  continue_trigger(object me);
int  cancel_trigger(object me);

int main(object me, string arg)
{
        object ob;
        object env;
        string msg, filename, file, *lines;
        string tg_msg, tg_cmd;
        int i, n, line;

        seteuid(getuid());

        filename=DATA_DIR+"trigger/"+query("id", me)+__SAVE_EXTENSION__;
        if( !arg) {
                if( file_size(filename) > 0 ) {
                        write(HIC"您目前已设定有的触发如下：\n"NOR);
                        file = read_file(filename);
                        msg = HIW"";

                        lines = explode(file, "\n");
                        for( i = 0; i < sizeof(lines); i++ ) {
                                if( sscanf(lines[i], "%s:%s", tg_msg, tg_cmd) ) {
                                        tg_cmd = replace_string(tg_cmd, ",", ";");
                                        msg += "-----------------------------------------------\n";
                                        msg += "(" + chinese_number(i+1) + ")\n";
                                        msg += HIY"触发字符："HIW + tg_msg + "\n";
                                        msg += HIY"触发指令："HIW + tg_cmd + "\n";
                                        msg += "-----------------------------------------------\n";
                                }
                        }

                        msg += "\n"NOR;
                        me->start_more(msg);

                        return 1;
                }
                else
                        return notify_fail(HIW"指令格式：trigger 触发字符:执行指令\n"HIY"[提示：如需设置多个指令，每个指令之间用逗号[,]间隔开]\n"NOR);
        }

        if( arg == "clear" ) {
                if( query("doing", me) == "trigger" )
                        return notify_fail("你现在正在执行触发，请先停下来再清除它。\n");

                delete("trigger", me);
                if( file_size(filename) >= 0 ) {
                        rm(filename);
                        write(HIW"成功清除触发设置。\n"NOR);
                        return 1;
                } else {
                        write(HIW"你并没有设置触发。\n"NOR);
                        return 1;
                }
        }

        if( sscanf(arg, "rm %d", line) ) {
                if( query("doing", me) == "trigger" )
                        return notify_fail("你现在正在执行触发，请先停下来再清除它。\n");

                if( file_size(filename) > 0 ) {
                        file = read_file(filename);
                        lines = explode(file, "\n");

                        if( line > sizeof(lines) )
                                return notify_fail(HIY"第 " + chinese_number(line) +" 条触发设置不存在。\n"NOR);

                        msg = "";

                        for( i = 0; i < sizeof(lines); i++ ) {
                                if( i + 1 == line ) {
                                        if( sscanf(lines[i], "%s:%s", tg_msg, tg_cmd) ) {
                                                tg_cmd = replace_string(tg_cmd, ",", ";");
                                                write(HIR"你成功删除第" + chinese_number(line) + "条触发如下：\n");
                                                write("-----------------------------------------------\n");
                                                write(HIY"触发字符："HIW + tg_msg + "\n");
                                                write(HIY"触发指令："HIW + tg_cmd + "\n");
                                                write("-----------------------------------------------\n");
                                        }

                                        continue;
                                }

                                msg += lines[i] + "\n";
                        }
                        rm(filename);
                        write_file(filename, msg, 1);
                        return 1;
                }
                else
                        return notify_fail(HIY"你目前并没有触发设置。\n"NOR);
        }
        if( arg == "start" ) {
                return notify_fail("目前该功能暂时关闭。\n");
                if( file_size(filename) < 1 )
                        return notify_fail("你目前还没有制订触发。\n");

                if( query("trigger", me) )
                        return notify_fail(HIY"你并没有关闭触发功能，不需要再开启。\n"NOR);

                if( query("doing", me) )
                        return notify_fail("你现在正在忙于锻炼，不能开展新触发。\n");

                env = environment(me);
                if( !env )
                        return notify_fail("你现在什么都做不了。\n");

                if( env->is_chat_room() )
                        return notify_fail("你不能在聊天室里面执行计划。\n");

                if( query("combat_exp", me)<5000 )
                        return notify_fail("你的实战经验太浅薄，还是先好好锻炼锻炼再说吧。\n");

                if( query("potential", me)-query("learned_points", me)<100 )
                        return notify_fail("你的潜能太少，难以开展触发。\n");

                if( sizeof(filter_array(all_inventory(env), (: userp :))) > 12 )
                        return notify_fail("这里的人实在太多了，你难以静心开展触发。\n");

                addn("learned_points", 100, me);

                file = read_file(filename);
                set("trigger", file, me);
                write(HIG"你开启了触发功能。\n"NOR);
                set("startroom", base_name(env), me);
                CLOSE_D->user_closed(me);
                me->set_short_desc(0);
                continue_trigger(me);
                return 1;
        }

        if( query("doing", me) == "trigger" )
                return notify_fail("你现在正在执行触发，请先停下来再修改。\n");

        if( strlen(arg) > 300 )
                return notify_fail(HIY"你的触发设定太长了，请控制在300个字节以内，\n"NOR);

        if( file_size(filename) > 0 ) {
                file = read_file(filename);
                lines = explode(file, "\n");

                if( sizeof(lines) >= TRIGGER_CMD_SIZE )
                        return notify_fail(HIY"你只能设置" + chinese_number(TRIGGER_CMD_SIZE) + "条触发，需要删除一些触发才能继续设置。\n"NOR);
        }

        if( sscanf(arg, "%s:%s", tg_msg, tg_cmd) ) {
                if( !tg_msg || !tg_cmd )
                        write(HIW"增加触发失败。\n"NOR);
                else
                if( write_file(filename, tg_msg + ":" + tg_cmd + "\n") ) {
                        tg_cmd = replace_string(tg_cmd, ",", ";");
                        write(HIG"你成功增加了一条触发如下：\n");
                        write("-----------------------------------------------\n");
                        write(HIY"触发字符："HIW + tg_msg + "\n");
                        write(HIY"触发指令："HIW + tg_cmd + "\n");
                        write("-----------------------------------------------\n");
                }
                else
                        write(HIW"增加触发失败。\n"NOR);
        }
        else
                return notify_fail(HIW"指令格式：trigger 触发字符:执行指令\n"HIY"[提示：如需设置多个指令，每个指令之间用逗号[,]间隔开]\n"NOR);

        return 1;

}

// 开始执行触发
int continue_trigger(object me)
{
        if( !query("trigger", me) )
                return 0;

        set("doing", "trigger", me);
        me->set_override("unconcious", (: call_other, __FILE__, "cancel_trigger" :));
        me->set_override("die", (: call_other, __FILE__, "cancel_trigger" :));
        return 1;
}

// 中止触发
int cancel_trigger(object me)
{
        me->delete_override("unconcious");
        me->delete_override("die");

        if( !query("trigger", me) )
                return 0;

        delete("trigger", me);
        delete_temp("trigger", me);
        CLOSE_D->user_opened(me);

        if( !interactive(me) )
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 0);

        return 0;
}

// 执行触发中
void execute_trigger(object me)
{
        string cmd, *cmds, *run;
        string cmd_buffer;
        int i, n;

        if( !objectp(me) || previous_object() != me )
                return;

        if( !(cmd=query_temp("trigger", me)) )
                return;

#ifndef NO_FEE
        if( !interactive(me) &&
            !me->is_vip() && query("online_time", me) <= query("offline_time", me)*3){
                cancel_trigger(me);
                return;
        }
#endif

        cmds = explode(cmd, ",");
        n = sizeof(cmds);
        run = ({ });

        for( i=0; i<n; i++ ) {
                if( i >= MAX_TRIGGER_CMDS ) break;
                if( me->is_busy() || !living(me) ) break;
                if( query("jing", me)*100/query("max_jing", me)<5 || 
                    query("qi", me)*100/query("max_qi", me)<5 )
                        break;
                if( query_temp("block_msg", me) || me->is_block_cmds() )
                        break;

                me->force_me(cmds[i]);
                run += ({ cmds[i] });
        }

        cmds -= run;

        if( !arrayp(cmds) || !sizeof(cmds) ) {
                delete_temp("trigger", me);
        } else {
                cmd_buffer = implode(cmds, ",");
                set_temp("trigger", cmd_buffer, me);
        }

        return;
}

void user_quit(object me)
{
        if( !is_root(previous_object()) &&
            previous_object() != me )
                return;

        if( !objectp(me) )
                return;

        me->force_me("quit");

        if( objectp(me) && !interactive(me) )
                me->start_call_out((: call_other, __FILE__, "user_quit", me :), 5);
}

int help (object me)
{
       write(@HELP
指令格式：
[一]、增加一条触发：trigger 触发字符:执行指令
      例如：我想触发“运功完毕”，也就是屏幕上出现“运功完毕”，我就
      让他打坐练内，那么我们可以如下面这么设置：
      trigger 运功完毕:dazuo 100
      执行看看，你会发现只要屏幕上一出现“运功完毕”这些字，系统就会
      自动帮你用100点内力打坐。
      也许你会问：如果我想屏幕上出现“运功完毕”就先读书一次再打坐，
      也就是屏幕上出现“运功完毕”时同时执行两个指令，那怎么设置呢？
      很简单，你只需要把各个指令之间用逗号[,]间隔开就可以了。如下：
      trigger 运功完毕:study book,dazuo 100
      系统就会在屏幕上出现“运功完毕”时就先帮你读书读书一次再打坐了。
      当然也同离线计划练功一样也是支持 alias 简化指令的。
[二]：查看设置的所有触发：trigger
[三]：删除一条触发：trigger rm 数字
      说明：这个数字就是你要删除的那条触发的位置，可以通过查看你要删
      除的那条触发的位置。
[四]：删除所有触发：trigger clear
[五]：关闭触发：halt
[六]：启动触发：trigger start

see also: scheme
HELP
        );
        return 1;
}
