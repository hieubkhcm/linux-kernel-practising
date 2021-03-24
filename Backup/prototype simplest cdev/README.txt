18Mar21
Chương trình C dùng để tạo ra một loadable kernel module LKM (.ko) có liên kết với file 

- Trong quá trình __init() thì đăng ký class rồi tạo ra file trong /dev để thao tác qua các io của file như .open .close .read .release

- Để tạo ra được file trong /dev thì cần có một số thủ tục như sau:
	- Lấy số major minor 
	- Tạo class
	- Tạo device trong /dev
	- init cái cdev 
	- add vô kernel
	
- có file rồi thì tất nhiên phải quan tâm tới làm gì với file đó nên mỗi io open release read write thì coder tự viết, không có vấn đề gì nữa rồi nhé.

Summary:
__init __exit ---> phục vụ gắn vào gõ ra cửa .ko
fops ---> phục vụ việc file có chức năng gì, chức năng nào khởi chạy đoạn code nào
allo_region gì gì đó ---> để lấy đươc cặp số maj minor nhét vô dev_t
thủ tục tạo ra file trong /dev ---> coi trong code có giải thích rõ
	