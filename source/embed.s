    .section .rodata
    .global gtaPayload
    .type   gtaPayload, @object
    .align  4
gtaPayload:
    .incbin "rdr2Payload/gtaPayload.bin"
gtaPayloadEnd:
    .global gtaPayloadSize
    .type   gtaPayloadSize, @object
    .align  4
gtaPayloadSize:
    .int    gtaPayloadEnd - gtaPayload
