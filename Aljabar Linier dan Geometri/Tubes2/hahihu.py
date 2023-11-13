# import cv2
# import numpy as np
# import time
# import cosine_similiarity

# def ImageToMatrix(path):
#     img_bgr = cv2.imread(path)
#     img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB).astype('float64')
#     return img_rgb

# def RGBtoHSV(rgb_matrix):
#     rgb_normalized = rgb_matrix / 255.0
#     r, g, b = rgb_normalized[:, :, 0], rgb_normalized[:, :, 1], rgb_normalized[:, :, 2]

#     Cmax = np.max(rgb_normalized, axis=-1)
#     Cmin = np.min(rgb_normalized, axis=-1)
#     Delta = Cmax - Cmin

#     h = np.where(Delta == 0, 0,
#                 np.where(Cmax == r, 60 * ((g - b) / Delta % 6), #Kasus Cmax = r
#                 np.where(Cmax == g, 60 * ((b - r) / Delta + 2), #Kasus Cmax = g
#                 60 * ((r - g) / Delta + 4))))                   #Kasus Cmax = b

#     s = np.where(Cmax == 0, 0, Delta / Cmax)
#     v = Cmax

#     hsv_matrix = np.dstack((h, s, v))
    
#     return hsv_matrix


# # def create_histogram(hsv_matrix):
# #     mod3_width = (hsv_matrix.shape[1] // 3) * 3
# #     mod3_length = (hsv_matrix.shape[0] // 3) * 3

# #     mod3_hsv_matrix = hsv_matrix[:mod3_length,:mod3_width]

# #     reshaped_matrix = mod3_hsv_matrix.reshape(hsv_matrix.shape[0] // 3, 3, hsv_matrix.shape[1] // 3, 3, 3)
# #     downsampled_matrix = np.mean(reshaped_matrix, axis=(1, 3))
# #     h_channel = downsampled_matrix[:, :, 0]
# #     s_channel = downsampled_matrix[:, :, 1]
# #     v_channel = downsampled_matrix[:, :, 2]

# #     # h_channel = hsv_matrix[:, :, 0]
# #     # s_channel = hsv_matrix[:, :, 1]
# #     # v_channel = hsv_matrix[:, :, 2]
    
# #     # h_bins = [0, 45,90, 135, 180, 225, 270, 315, 360]
# #     # s_bins = [0, 0.33, 0.66, 1]
# #     # v_bins = [0, 0.33, 0.66, 1]

# #     h_bins = [0, 25, 40, 120, 190, 270, 295, 315, 361]
# #     s_bins = [0, 0.2, 0.7, 1]
# #     v_bins = [0, 0.2, 0.7, 1]

# #     hist_h, bin_edges_h = np.histogram(h_channel, bins=h_bins)
# #     hist_s, bin_edges_s = np.histogram(s_channel, bins=s_bins)
# #     hist_v, bin_edges_v = np.histogram(v_channel, bins=v_bins)

# #     concat = np.concatenate((hist_h, hist_s, hist_v))
# #     # concat = [hist_h, hist_s, hist_v]

# #     return concat

# # # def colour_similiarity(hsv1,hsv2):

# def create_histogram_downsample(hsv_matrix):
#     mod3_width = (hsv_matrix.shape[1] // 3) * 3
#     mod3_length = (hsv_matrix.shape[0] // 3) * 3

#     mod3_hsv_matrix = hsv_matrix[:mod3_length,:mod3_width]

#     reshaped_matrix = mod3_hsv_matrix.reshape(hsv_matrix.shape[0] // 3, 3, hsv_matrix.shape[1] // 3, 3, 3)
#     downsampled_matrix = np.mean(reshaped_matrix, axis=(1, 3))
#     h_channel = downsampled_matrix[:, :, 0]
#     s_channel = downsampled_matrix[:, :, 1]
#     v_channel = downsampled_matrix[:, :, 2]

#     h_bins = [0, 25, 40, 120, 190, 270, 295, 315, 361]
#     s_bins = [0, 0.2, 0.7, 1]
#     v_bins = [0, 0.2, 0.7, 1]

#     hist_h, bin_edges_h = np.histogram(h_channel, bins=h_bins)
#     hist_s, bin_edges_s = np.histogram(s_channel, bins=s_bins)
#     hist_v, bin_edges_v = np.histogram(v_channel, bins=v_bins)

#     concat = np.concatenate((hist_h, hist_s, hist_v))

#     return concat

# def create_histogram(hsv_matrix):
#     h_channel = hsv_matrix[:, :, 0]
#     s_channel = hsv_matrix[:, :, 1]
#     v_channel = hsv_matrix[:, :, 2]

#     h_bins = [0, 25, 40, 120, 190, 270, 295, 315, 361]
#     s_bins = [0, 0.2, 0.7, 1]
#     v_bins = [0, 0.2, 0.7, 1]

#     hist_h, bin_edges_h = np.histogram(h_channel, bins=h_bins)
#     hist_s, bin_edges_s = np.histogram(s_channel, bins=s_bins)
#     hist_v, bin_edges_v = np.histogram(v_channel, bins=v_bins)

#     concat = np.concatenate((hist_h, hist_s, hist_v))

#     return concat


# stime = time.time()
# hsv_matrix_1 = RGBtoHSV(ImageToMatrix("src/948.jpg"))
# histogram_1 = create_histogram(hsv_matrix_1)
# hsv_matrix_2 = RGBtoHSV(ImageToMatrix("src/waifu2.jpeg"))
# histogram_2 = create_histogram(hsv_matrix_2)

# histogram_1_downsample = create_histogram_downsample(hsv_matrix_1)
# histogram_2_downsample = create_histogram_downsample(hsv_matrix_2)

# similiarity = cosine_similiarity.cosine_similiarity(histogram_1,histogram_2)
# similiarity_downsample = cosine_similiarity.cosine_similiarity(histogram_1_downsample,histogram_2_downsample)
# print("result normal: ", similiarity)
# print("result downsample: ", similiarity_downsample)

# ftime = time.time()
# print(ftime-stime)

import cv2
import numpy as np
import warnings
import time

warnings.filterwarnings("ignore", category=RuntimeWarning)

def cosine_similarity(v1, v2):
    dot_prod = np.dot(v1, v2)
    norm_v1 = np.linalg.norm(v1)
    norm_v2 = np.linalg.norm(v2)
    if norm_v1 == 0 or norm_v2 == 0:
        return 0
    else:
        return (dot_prod / (norm_v1 * norm_v2))

def image_to_matrix(path):
    img_bgr = cv2.imread(path)
    img_rgb = cv2.cvtColor(img_bgr, cv2.COLOR_BGR2RGB).astype('float64')
    return img_rgb

def rgb_to_hsv(rgb_matrix):
    rgb_normalized = rgb_matrix / 255.0
    r, g, b = rgb_normalized[:, :, 0], rgb_normalized[:, :, 1], rgb_normalized[:, :, 2]

    Cmax = np.max(rgb_normalized, axis=-1)
    Cmin = np.min(rgb_normalized, axis=-1)
    Delta = Cmax - Cmin

    h = np.where(Delta == 0, 0,
                 np.where(Cmax == r, 60 * ((g - b) / Delta % 6),
                          np.where(Cmax == g, 60 * ((b - r) / Delta + 2),
                                   60 * ((r - g) / Delta + 4))))

    s = np.where(Cmax == 0, 0, Delta / Cmax)
    v = Cmax

    hsv_matrix = np.dstack((h, s, v))

    return hsv_matrix

def create_histogram(hsv_matrix):
    h_bins = [0, 25, 40, 120, 190, 270, 295, 315, 361]
    s_bins = [0, 0.2, 0.7, 1]
    v_bins = [0, 0.2, 0.7, 1]

    hist_h, _ = np.histogram(hsv_matrix[:, :, 0], bins=h_bins)
    hist_s, _ = np.histogram(hsv_matrix[:, :, 1], bins=s_bins)
    hist_v, _ = np.histogram(hsv_matrix[:, :, 2], bins=v_bins)

    concat = np.concatenate((hist_h, hist_s, hist_v))

    return concat

def split_image_into_blocks(image, num_blocks=3):
    block_size = image.shape[0] // num_blocks
    blocks = [image[i:i + block_size, j:j + block_size] for i in range(0, image.shape[0], block_size) for j in range(0, image.shape[1], block_size)]
    return blocks

def compute_histogram_similarity(hist1, hist2):
    return cosine_similarity(hist1, hist2)

def main():
    # Load two images
    image1 = image_to_matrix('waifu2.jpeg')
    image2 = image_to_matrix('948.jpg')

    # Split the images into 3x3 blocks
    num_blocks = 3
    blocks1 = split_image_into_blocks(image1, num_blocks)
    blocks2 = split_image_into_blocks(image2, num_blocks)

    # Create a list to store the block similarities
    block_similarities = []

    for block1, block2 in zip(blocks1, blocks2):
        # Convert blocks to HSV
        hsv_block1 = rgb_to_hsv(block1)
        hsv_block2 = rgb_to_hsv(block2)

        # Create histograms for the blocks
        hist1 = create_histogram(hsv_block1)
        hist2 = create_histogram(hsv_block2)

        # Compute the cosine similarity for the current pair of blocks
        similarity = compute_histogram_similarity(hist1, hist2)
        block_similarities.append(similarity)

    # Average the block similarities to get the final result
    final_similarity = np.mean(block_similarities)
    print("Final Cosine Similarity:", final_similarity)

if __name__ == "__main__":
    stime = time.time()
    main()
    ftime = time.time()
    print(ftime-stime)


