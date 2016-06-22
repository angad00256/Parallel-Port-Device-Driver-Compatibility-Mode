struct file_operations fops=
{
	open : dev_open,
	write : dev_write,
	read : dev_read
/*	release : dev_release,
	llseek : dev_seek
*/
};
