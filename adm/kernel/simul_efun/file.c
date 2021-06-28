// file.c

#include <runtime_config.h>

void cat(string file)
{
        if( previous_object() )
                seteuid(geteuid(previous_object()));
        else
                seteuid(ROOT_UID);
        write(read_file(file));
}

void assure_file(string file)
{
        string path, *dir;
        int i;

        if( file_size(file) != -1 ) return;

        seteuid(ROOT_UID);
        dir = explode(file, "/");

        if( file[strlen(file) - 1] != '/' )
                // the file is refer to a file, not directory
                dir = dir[0..sizeof(dir)-2];

        path = "/";
        for( i = 0; i < sizeof(dir); i++ ) {
                path += dir[i];
                mkdir(path);
                path += "/";
        }

        dir = 0;
        seteuid(getuid());
}

void log_file(string file, string text)
{
        seteuid(ROOT_UID);
        assure_file(LOG_DIR + file);
        write_file(LOG_DIR + file, text);
}

/*
#define DEFAULT_LOG_FILES       20

varargs void log_file(string file, string text, int backup)
{
        string month, ctime, timedesc;

        object this_player = this_player(1);

        if( !stringp(file) || !stringp(text) ) return;

        seteuid(ROOT_UID);
        assure_file(LOG_DIR + file);

        file = LOG_DIR + file;

#ifdef LONELY_IMPROVED
        text = remove_ansi(text);
#endif
        if( text[<1] != '\n' ) text += "\n";

        //if( file_size(file)+strlen(text) > get_config(__MAX_READ_FILE_SIZE__) )
        if( file_size(file)+strlen(text) > 1024000 )
        {
                int i;

                while(file_size(file+"."+(++i)) > 0);

                while(--i)
                {
                        if( !undefinedp(backup) )
                        {
                                // backup == -1 时为无限
                                if( backup != -1 && i >= backup )
                                {
                                        rm(file+"."+i);
                                        continue;
                                }
                        }
                        else if( i >= DEFAULT_LOG_FILES )
                        {
                                rm(file+"."+i);
                                continue;
                        }

                        rename(file+"."+i, file+"."+(i+1));
                }
                rename( file, file+"."+1 );
        }

        if( objectp(this_player) )
        {
                string ip = query_ip_number(this_player);

                text = (query("id", this_player)) + (ip ? "("+ip+") " :" ") + text;
        }

        ctime = ctime(time());

        switch(ctime[4..6])
        {
                case "Jan"      :       month = "01";break;
                case "Feb"      :       month = "02";break;
                case "Mar"      :       month = "03";break;
                case "Apr"      :       month = "04";break;
                case "May"      :       month = "05";break;
                case "Jun"      :       month = "06";break;
                case "Jul"      :       month = "07";break;
                case "Aug"      :       month = "08";break;
                case "Sep"      :       month = "09";break;
                case "Oct"      :       month = "10";break;
                case "Nov"      :       month = "11";break;
                case "Dec"      :       month = "12";break;
        }

        timedesc = sprintf("%s/%s/%s %s", month, (ctime[8]==' '?"0"+ctime[9..9]:ctime[8..9]), ctime[<4..<1], ctime[11..15]);

        write_file( file, timedesc+" "+text );
}
*/

#define SYSLOG_DIR       LOG_DIR+"syslog/"
nomask void sys_log(string file,string text)
{
        seteuid(ROOT_UID);
        assure_file(SYSLOG_DIR + file);
        write_file(SYSLOG_DIR + file, text);
}

string base_name(object ob)
{
        string file;

        if( !objectp(ob) ) return "";
#ifdef LONELY_IMPROVED
        return efun::base_name(ob);
#else
        if( sscanf(file_name(ob), "%s#%*d", file) == 2 )
                return file;
        else
                return file_name(ob);
#endif
}

string color_filter(string content)
{
        if (! content)
                return "";

        // Foreground color
        content = replace_string(content, "$BLK$", BLK);
        content = replace_string(content, "$RED$", RED);
        content = replace_string(content, "$GRN$", GRN);
        content = replace_string(content, "$YEL$", YEL);
        content = replace_string(content, "$BLU$", BLU);
        content = replace_string(content, "$MAG$", MAG);
        content = replace_string(content, "$CYN$", CYN);
        content = replace_string(content, "$WHT$", WHT);
        content = replace_string(content, "$HIR$", HIR);
        content = replace_string(content, "$HIG$", HIG);
        content = replace_string(content, "$HIY$", HIY);
        content = replace_string(content, "$HIB$", HIB);
        content = replace_string(content, "$HIM$", HIM);
        content = replace_string(content, "$HIC$", HIC);
        content = replace_string(content, "$HIW$", HIW);
        content = replace_string(content, "$HIK$", HIK);
        content = replace_string(content, "$NOR$", NOR);

        // Background color
        content = replace_string(content, "$BBLK$", BBLK);
        content = replace_string(content, "$BRED$", BRED);
        content = replace_string(content, "$BGRN$", BGRN);
        content = replace_string(content, "$BYEL$", BYEL);
        content = replace_string(content, "$BBLU$", BBLU);
        content = replace_string(content, "$BMAG$", BMAG);
        content = replace_string(content, "$BCYN$", BCYN);
        content = replace_string(content, "$BWHT$", BWHT);
        content = replace_string(content, "$HBRED$", HBRED);
        content = replace_string(content, "$HBGRN$", HBGRN);
        content = replace_string(content, "$HBYEL$", HBYEL);
        content = replace_string(content, "$HBBLU$", HBBLU);
        content = replace_string(content, "$HBMAG$", HBMAG);
        content = replace_string(content, "$HBCYN$", HBCYN);
        content = replace_string(content, "$HBWHT$", HBWHT);

        content = replace_string(content, "$U$", U);
        content = replace_string(content, "$BLINK$", BLINK);
        content = replace_string(content, "$REV$", REV);
        content = replace_string(content, "$HIREV$", HIREV);
        content = replace_string(content, "$BOLD$", BOLD);

        content = replace_string(content, "$REDGRN$", REDGRN);
        content = replace_string(content, "$REDYEL$", REDYEL);
        content = replace_string(content, "$REDBLU$", REDBLU);
        content = replace_string(content, "$REDMAG$", REDMAG);
        content = replace_string(content, "$REDCYN$", REDCYN);
        content = replace_string(content, "$REDWHI$", REDWHI);
        content = replace_string(content, "$GRNRED$", GRNRED);
        content = replace_string(content, "$GRNYEL$", GRNYEL);
        content = replace_string(content, "$GRNBLU$", GRNBLU);
        content = replace_string(content, "$GRNMAG$", GRNMAG);
        content = replace_string(content, "$GRNCYN$", GRNCYN);
        content = replace_string(content, "$GRNWHI$", GRNWHI);
        content = replace_string(content, "$YELRED$", YELRED);
        content = replace_string(content, "$YELGRN$", YELGRN);
        content = replace_string(content, "$YELBLU$", YELBLU);
        content = replace_string(content, "$YELMAG$", YELMAG);
        content = replace_string(content, "$YELCYN$", YELCYN);
        content = replace_string(content, "$YELWHI$", YELWHI);
        content = replace_string(content, "$BLURED$", BLURED);
        content = replace_string(content, "$BLUGRN$", BLUGRN);
        content = replace_string(content, "$BLUYEL$", BLUYEL);
        content = replace_string(content, "$BLUMAG$", BLUMAG);
        content = replace_string(content, "$BLUCYN$", BLUCYN);
        content = replace_string(content, "$BLUWHI$", BLUWHI);
        content = replace_string(content, "$MAGRED$", MAGRED);
        content = replace_string(content, "$MAGGRN$", MAGGRN);
        content = replace_string(content, "$MAGYEL$", MAGYEL);
        content = replace_string(content, "$MAGBLU$", MAGBLU);
        content = replace_string(content, "$MAGCYN$", MAGCYN);
        content = replace_string(content, "$MAGWHI$", MAGWHI);
        content = replace_string(content, "$CYNRED$", CYNRED);
        content = replace_string(content, "$CYNGRN$", CYNGRN);
        content = replace_string(content, "$CYNYEL$", CYNYEL);
        content = replace_string(content, "$CYNBLU$", CYNBLU);
        content = replace_string(content, "$CYNMAG$", CYNMAG);
        content = replace_string(content, "$CYNWHI$", CYNWHI);
        content = replace_string(content, "$WHIRED$", WHIRED);
        content = replace_string(content, "$WHIGRN$", WHIGRN);
        content = replace_string(content, "$WHIYEL$", WHIYEL);
        content = replace_string(content, "$WHIBLU$", WHIBLU);
        content = replace_string(content, "$WHIMAG$", WHIMAG);
        content = replace_string(content, "$WHICYN$", WHICYN);


        return content;
}

void color_cat(string file)
{
        if( previous_object() )
                seteuid(geteuid(previous_object()));
        else
                seteuid(ROOT_UID);

        write(color_filter(read_file(file)));
}

// filter color
varargs string filter_color(string arg, int raw)
{
        if (!arg)
                return "";
#ifdef __PACKAGE_ANSI__
        return efun::remove_ansi(arg);
#else
        arg = replace_string(arg, BLK, "");
        arg = replace_string(arg, RED, "");
        arg = replace_string(arg, GRN, "");
        arg = replace_string(arg, YEL, "");
        arg = replace_string(arg, BLU, "");
        arg = replace_string(arg, MAG, "");
        arg = replace_string(arg, CYN, "");
        arg = replace_string(arg, WHT, "");
        arg = replace_string(arg, HIR, "");
        arg = replace_string(arg, HIG, "");
        arg = replace_string(arg, HIY, "");
        arg = replace_string(arg, HIB, "");
        arg = replace_string(arg, HIM, "");
        arg = replace_string(arg, HIC, "");
        arg = replace_string(arg, HIW, "");
        arg = replace_string(arg, HIK, "");
        arg = replace_string(arg, NOR, "");
        arg = replace_string(arg, BOLD, "");
        arg = replace_string(arg, BLINK, "");

        if (raw)
        {
                arg = replace_string(arg, BBLK, "");
                arg = replace_string(arg, BRED, "");
                arg = replace_string(arg, BGRN, "");
                arg = replace_string(arg, BYEL, "");
                arg = replace_string(arg, BBLU, "");
                arg = replace_string(arg, BMAG, "");
                arg = replace_string(arg, BCYN, "");
                arg = replace_string(arg, HBRED, "");
                arg = replace_string(arg, HBGRN, "");
                arg = replace_string(arg, HBYEL, "");
                arg = replace_string(arg, HBBLU, "");
                arg = replace_string(arg, HBMAG, "");
                arg = replace_string(arg, HBCYN, "");
                arg = replace_string(arg, HBWHT, "");
                arg = replace_string(arg, REDGRN, "");
                arg = replace_string(arg, REDYEL, "");
                arg = replace_string(arg, REDBLU, "");
                arg = replace_string(arg, REDMAG, "");
                arg = replace_string(arg, REDCYN, "");
                arg = replace_string(arg, REDWHI, "");
                arg = replace_string(arg, GRNRED, "");
                arg = replace_string(arg, GRNYEL, "");
                arg = replace_string(arg, GRNBLU, "");
                arg = replace_string(arg, GRNMAG, "");
                arg = replace_string(arg, GRNCYN, "");
                arg = replace_string(arg, GRNWHI, "");
                arg = replace_string(arg, YELRED, "");
                arg = replace_string(arg, YELGRN, "");
                arg = replace_string(arg, YELBLU, "");
                arg = replace_string(arg, YELMAG, "");
                arg = replace_string(arg, YELCYN, "");
                arg = replace_string(arg, YELWHI, "");
                arg = replace_string(arg, BLURED, "");
                arg = replace_string(arg, BLUGRN, "");
                arg = replace_string(arg, BLUYEL, "");
                arg = replace_string(arg, BLUMAG, "");
                arg = replace_string(arg, BLUCYN, "");
                arg = replace_string(arg, BLUWHI, "");
                arg = replace_string(arg, MAGRED, "");
                arg = replace_string(arg, MAGGRN, "");
                arg = replace_string(arg, MAGYEL, "");
                arg = replace_string(arg, MAGBLU, "");
                arg = replace_string(arg, MAGCYN, "");
                arg = replace_string(arg, MAGWHI, "");
                arg = replace_string(arg, CYNRED, "");
                arg = replace_string(arg, CYNGRN, "");
                arg = replace_string(arg, CYNYEL, "");
                arg = replace_string(arg, CYNBLU, "");
                arg = replace_string(arg, CYNMAG, "");
                arg = replace_string(arg, CYNWHI, "");
                arg = replace_string(arg, WHIRED, "");
                arg = replace_string(arg, WHIGRN, "");
                arg = replace_string(arg, WHIYEL, "");
                arg = replace_string(arg, WHIBLU, "");
                arg = replace_string(arg, WHIMAG, "");
                arg = replace_string(arg, WHICYN, "");
        }
        return arg;
#endif
}

int noansi_strlen(string arg)
{
        return strlen(filter_color(arg, 1));
}
// 清理ansi色彩
string remove_ansi(string arg)
{
#ifdef __PACKAGE_ANSI__
        return efun::remove_ansi(arg);
#else
        arg = replace_string(arg, BLK, "");
        arg = replace_string(arg, RED, "");
        arg = replace_string(arg, GRN, "");
        arg = replace_string(arg, YEL, "");
        arg = replace_string(arg, BLU, "");
        arg = replace_string(arg, MAG, "");
        arg = replace_string(arg, CYN, "");
        arg = replace_string(arg, WHT, "");
        arg = replace_string(arg, HIR, "");
        arg = replace_string(arg, HIG, "");
        arg = replace_string(arg, HIY, "");
        arg = replace_string(arg, HIB, "");
        arg = replace_string(arg, HIM, "");
        arg = replace_string(arg, HIC, "");
        arg = replace_string(arg, HIW, "");
        arg = replace_string(arg, NOR, "");
        arg = replace_string(arg, BOLD, "");
        arg = replace_string(arg, BLINK, "");
        arg = replace_string(arg, BBLK, "");
        arg = replace_string(arg, BRED, "");
        arg = replace_string(arg, BGRN, "");
        arg = replace_string(arg, BYEL, "");
        arg = replace_string(arg, BBLU, "");
        arg = replace_string(arg, BMAG, "");
        arg = replace_string(arg, BCYN, "");
        arg = replace_string(arg, HBRED, "");
        arg = replace_string(arg, HBGRN, "");
        arg = replace_string(arg, HBYEL, "");
        arg = replace_string(arg, HBBLU, "");
        arg = replace_string(arg, HBMAG, "");
        arg = replace_string(arg, HBCYN, "");
        arg = replace_string(arg, HBWHT, "");
        return arg;
#endif
}

int file_lines(string file)
{
#ifdef BINARY_SUPPORT
        return efun::file_lines(file);
#else
        int i;
        int jmp;

        i = 65536;
        jmp = i / 2;

        while (jmp) {
                if( read_file(file, i, 1) ) i += jmp; else
                                            i -= jmp;
                jmp /= 2;
        }

        return i - 1;
#endif
}

int is_c_file(string arg)
{
        int l;

        l = strlen(arg);
        if( arg[l - 1] == 'c' && arg[l - 2] == '.' )
                return 1;

        return 0;
}


#define FILE_TYPE       ({ "", ".c", ".o", ".h" })

void intact_file_name(string filename)
{
        if( !filename ) return;

        foreach( string type in FILE_TYPE )
        {
                if( file_size(filename+type) >= 0 )
                {
                        filename += type;
                        break;
                }
        }
}

int file_exists(string filename)
{
        if( !stringp(filename) ) return 0;

        intact_file_name(filename);

        return file_size(filename) > 0;
}
