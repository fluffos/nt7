// This program is a part of NT MudLIB

#include <config.h>
#include <localtime.h>

// This is called when there is a driver segmentation fault or a bus error,
// etc.  As it's static it can't be called by anything but the driver (and
// master).
// 当发生了 driver segmentation fault 或 bus error 等错误时, 将呼叫此函式
protected void crash(string error, object command_giver, object current_object)
{
#if INSTALL_CRASH_SAVE
        object ob;
        string dump_dir;
        string user;
        string flogin, fuser;
        mixed lt;
#endif

        mixed cmds;
        int i;

        efun::shout("系统核心发出一声惨叫：哇—哩—咧—\n");
        efun::shout("系统核心告诉你：要当机了，自己保重吧！\n");

        log_file("static/CRASHES", MUD_NAME + " crashed on: " + ctime(time()) +", error: " + error + "\n");
        log_file("static/CRASHES", "command_giver: " + (command_giver ? file_name(command_giver) : "none") + "\n");
        log_file("static/CRASHES", "current_object: " + (current_object ? file_name(current_object) : "none") + "\n");
        log_file("static/CRASHES", "call_stack(0): "+sprintf("%O\n", call_stack(0)));
        log_file("static/CRASHES", "call_stack(1): "+sprintf("%O\n", call_stack(1)));
        log_file("static/CRASHES", "call_stack(2): "+sprintf("%O\n", call_stack(2)));
        log_file("static/CRASHES", "call_stack(3): "+sprintf("%O\n", call_stack(3)));

        if( command_giver ) {
                log_file("static/CRASHES",
                         sprintf("this_player: %O\n", command_giver));

                cmds = command_giver->query_commands();

                for (i = 0; i < sizeof(cmds); i++) {
                        if( cmds[i][2] == command_giver ) continue;
                        log_file("static/CRASHES",
                                 sprintf("%-15s  %2d %O\n", cmds[i][0], cmds[i][1], cmds[i][2]));
                }

                if( environment(command_giver) )
                        log_file("static/CRASHES",
                                 sprintf("in where: %s(%s)。\n", query("short", environment(command_giver)),
                                         base_name(environment(command_giver))));
        }

        if( current_object )
                log_file("static/CRASHES",
                         sprintf( "this_object: %O\n", current_object));

#if INSTALL_CRASH_SAVE
        lt = localtime(time());
        lt[LT_MON]++;
        dump_dir = sprintf(DUMP_DIR "%d-%d-%d/", lt[LT_YEAR], lt[LT_MON], lt[LT_MDAY]);
        foreach (ob in users()) {
                reset_eval_cost();

                // backup user data to dump
                user = geteuid(ob);
                if( !stringp(user) )
                        continue;
                flogin = "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__;
                fuser  = "user/"  + user[0..0] + "/" + user + __SAVE_EXTENSION__;
                if( file_size(DATA_DIR + flogin) > 0 &&
                    file_size(DATA_DIR + fuser) > 0 ) {
                        // exist in data, I will backup it to dump
                        assure_file(dump_dir + flogin);
                        assure_file(dump_dir + fuser);
                        efun::cp(DATA_DIR + flogin, dump_dir + flogin);
                        efun::cp(DATA_DIR + fuser,  dump_dir + fuser);
                        log_file("static/dump",
                                 sprintf("backup user(%s) to dump\n", user));
                }
                catch(ob->save());
        }

        /*
        foreach( ob in objects() )
        {
                reset_eval_cost();
                catch(ob->remove());
        }
        */
        efun::shout("【存盘精灵】：您的档案已经紧急保存了。");
#endif
}
