# Luồng hoat động:
Có các service sau:
## Publish
- Có 1 mảng, gọi là mảng data
- Kiểm tra xem mảng data có phần tử hay không để publish với nội dung tương ứng
- Data là mảng string với các phần tử dạng:  ten_topic:du_lieu_truyen_di

## Subscribe
- Subsribe topic máy bơm và đèn
- Dữ liệu nhận được:
- Máy bơm: Thời gian bật máy bơm
- Đèn: Thời gian bật đèn

## Đo nhiệt độ, độ ẩm không khí rồi lưu vào biến
- Đo định kỳ 30s 1 lần
- Lưu biến thời gian đo gần nhất
- Lưu biến đo độ ẩm không khí
- Lưu biến đo nhiệt độ không khí
- Khi chạy thì sẽ kiểm tra thời gian đo gần nhất + 30s có nhỏ hơn thời gian hiện tại không, nếu nhỏ hơn thì đo, không thì thôi

## Đo độ ẩm đắt rồi lưu vào biến
- Đo định kỳ 30s 1 lần
- Lưu biến thời gian đo gần nhất
- Lưu biến đo độ ẩm đất
- Khi chạy thì sẽ kiểm tra thời gian đo gần nhất + 30s có nhỏ hơn thời gian hiện tại không, nếu nhỏ hơn thì đo, không thì thôi

## Xử lý hành động bật/tắt máy bơm
- Lưu biến thời gian thực hiện gần nhất
- Lưu biến trạng thái máy bơm
- Lưu biến thời gian bật máy bơm (0 có nghĩa là không làm gì)
- Đầu tiên: Thời gian thực hiện gần nhất là 0, trạng thái máy bơm không hoạt động
- Khi nhận được tín hiệu bơm, thời gian bật máy bơm bằng 10s
- Nếu thời gian bật máy bơm bằng 0 và trạng thái máy bơm đang bật thì tắt máy bơm
- Nếu máy bơm chưa bật, thì sẽ bật máy bơm và lưu thời gian thực hiện gần nhất
- Nếu máy bơm đã bật và thời gian thực hiện gần nhất + thời gian bật máy bơm <= thời gian hiện tại thì tắt máy bơm và reset thời gian bật máy bơm bằng 0

## Xừ lý hành động bật/tắt đèn
- Lưu biến thời gian thực hiện gần nhất
- Lưu biến trạng thái đèn
- Lưu biến thời gian bật đèn (0 có nghĩa là không làm gì)
- Đầu tiên: Thời gian thực hiện gần nhất là 0, trạng thái đèn không hoạt động
- Khi nhận được tín hiệu đèn, thời gian bật đèn bằng 10s
- Nếu thời gian bật đèn bằng 0 và trạng thái đèn đang bật thì tắt đèn
- Nếu đèn chưa bật, thì sẽ bật đèn và lưu thời gian thực hiện gần nhất
- Nếu đèn đã bật và thời gian thực hiện gần nhất + thời gian bật đèn <= thời gian hiện tại thì tắt đèn và reset thời gian bật đèn bằng 0

# Bản tin

## publish ground_topic

```json
{
    "h": 98.73
}
```
- h: độ ẩm đất, đơn vị %

## publish air_topic

```json
{
    "h": 98.73,
    "t": 30
}
```
- h: độ ẩm không khí, đơn vị %
- t: nhiệt độ không khí, đơn vị độ C

## subscribe pump_topic

```json
{
    "t": 30
}
```
- t: Bật máy bơm trong 30s

## subscribe lamp_topic

```json
{
    "t": 30
}
```
- t: Bật đèn trong 30s

# Ví dụ:

Bật đèn trong 1 tiếng
```
mosquitto_pub -h localhost -t lamp_topic -m "{\"t\":3600}"
```

Bật bơm trong 15 phút
```
mosquitto_pub -h localhost -t pump_topic -m "{\"t\":900}"
```
